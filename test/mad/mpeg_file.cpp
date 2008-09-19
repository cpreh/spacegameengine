#include "mpeg_file.hpp"
#include <sge/log/headers.hpp>
#include <sge/raw_vector_impl.hpp>

sge::mad::mpeg_file::mpeg_file(path const &p)
	: stdstream(p),
	  s(stdstream)
{
	SGE_LOG_DEBUG(log::global(),log::_1 << "mad: constructing mpeg file");

	s.decode(f);

	channels_ = f.channels();
	sample_rate_ = f.sample_rate();

	SGE_LOG_INFO(
		log::global(),
		log::_1 << "mad: file info: \n" << f.info());

	syn.synthesize(f,buffered_samples,channels());
}

sge::mad::mpeg_file::sample_type sge::mad::mpeg_file::read(
	sample_type const samples,
	raw_array_type &dest)
{
	SGE_LOG_DEBUG(
		log::global(),
		log::_1 << "requested " << samples << " samples, got " << buffered_samples.size()/bytes_per_sample() << " samples in buffer");

	// there are enough buffered samples to meet the request
	if (static_cast<sample_type>(buffered_samples.size()/bytes_per_sample()) >= samples)
	{
		std::copy(
			buffered_samples.begin(),
			buffered_samples.begin()+(samples*bytes_per_sample()),
			std::back_inserter(dest));

		buffered_samples.erase(
			buffered_samples.begin(),
			buffered_samples.begin()+(samples*bytes_per_sample()));

		return samples;
	}

	if (s.eof())
	{
		SGE_LOG_DEBUG(
			log::global(),
			log::_1 << "at end of file, returning zero samples");

		return static_cast<sge::mad::mpeg_file::sample_type>(0);
	}

	SGE_LOG_DEBUG(
		log::global(),
		log::_1 << "putting " << buffered_samples.size() << " bytes into destination");
	std::copy(buffered_samples.begin(),buffered_samples.end(),std::back_inserter(dest));

	sample_type const remaining_samples = 
		static_cast<sample_type>(samples - buffered_samples.size()/bytes_per_sample());

	SGE_LOG_DEBUG(
		log::global(),
		log::_1 << "remaining " << remaining_samples << " samples");
	
	buffered_samples.clear();

	s.decode(f);

	raw_array_type temp;
	syn.synthesize(f,temp,channels());

	// not all samples could be read?
	if (static_cast<sample_type>(temp.size()/bytes_per_sample()) < remaining_samples)
	{
		std::copy(temp.begin(),temp.end(),std::back_inserter(dest));
	}
	else
	{
		// copy the requested amount to dest...
		std::copy(
			temp.begin(),
			temp.begin()+remaining_samples*bytes_per_sample(),
			std::back_inserter(dest));

		// and update buffered samples
		std::copy(
			temp.begin()+remaining_samples*bytes_per_sample(),
			temp.end(),
			std::back_inserter(buffered_samples));
	}
	
	return static_cast<sample_type>(dest.size());
}

sge::mad::mpeg_file::sample_type sge::mad::mpeg_file::read_all(raw_array_type &dest)
{
	while (!s.eof())
		read(static_cast<sample_type>(1024),dest);
	return dest.size();
}

void sge::mad::mpeg_file::reset()
{

}
