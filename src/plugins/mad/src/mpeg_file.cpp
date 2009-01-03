#include "../mpeg_file.hpp"
#include "../log.hpp"
#include <sge/raw_vector_impl.hpp>
#include <sge/audio/exception.hpp>
#include <sge/text.hpp>
#include <algorithm>
#include <iterator>

namespace
{
template<typename T,typename U>
void append(T &t,U const &u)
{
	std::copy(u.begin(),u.end(),std::back_inserter(t));
}

template<typename S,typename T,typename U>
void move(S &container,T it,T const end,U dest)
{
	std::copy(it,end,dest);
	container.erase(it,end);
}
}

sge::mad::mpeg_file::mpeg_file(
	filesystem::path const &p)
:
	stdstream(p),
	s(stdstream)
{
	if (!stdstream.is_open())
		throw audio::exception(
			SGE_TEXT("couldn't open file \"")
			+ p.string()
			+ SGE_TEXT('"'));
	
	// throw away first frame if it's the id3 tag
	char id3[3];
	stdstream.read(id3,static_cast<std::streamsize>(3));
	stdstream.clear();
	stdstream.seekg(static_cast<std::streamoff>(0),std::ios_base::beg);

	frame &f = std::string(id3,id3+3) == "ID3" 
		? s.decode(decoding_mode::recover) 
		: s.decode(decoding_mode::strict);

	sample_rate_ = f.sample_rate();

	SGE_LOG_INFO(
		log(),
		log::_1 << SGE_TEXT("mad: file info: \n") << f.info());

	append(buffered_,f.synthesize());
}

sge::mad::mpeg_file::sample_count sge::mad::mpeg_file::read(
	sample_count const samples,
	sample_container &dest)
{
	SGE_LOG_DEBUG(log(),log::_1 << SGE_TEXT("reading ") << samples << SGE_TEXT(" samples"));

	if (s.eof())
	{
		SGE_LOG_DEBUG(log(),log::_1 << SGE_TEXT("we're at the end"));
		return static_cast<sample_count>(0);
	}

	sample_count const samples_bytes = 
		static_cast<sample_count>(samples*bytes_per_sample());

	move(buffered_,buffered_.begin(),buffered_.end(),std::back_inserter(dest));

	while (dest.size() < samples_bytes && !s.eof())
		append(dest,s.decode(decoding_mode::recover).synthesize());
	
	move(dest,dest.begin()+samples_bytes,dest.end(),std::back_inserter(buffered_));

	return dest.size()/bytes_per_sample();
}

sge::mad::mpeg_file::sample_count sge::mad::mpeg_file::read_all(sample_container &dest)
{
	SGE_LOG_DEBUG(log(),log::_1 << SGE_TEXT("reading all samples"));

	if (s.eof() && buffered_.empty())
	{
		SGE_LOG_DEBUG(log(),log::_1 << SGE_TEXT("we're at the end"));
		return static_cast<sample_count>(0);
	}

	move(buffered_,buffered_.begin(),buffered_.end(),std::back_inserter(dest));

	while (!s.eof())
		append(dest,s.decode(decoding_mode::recover).synthesize());

	return dest.size()/bytes_per_sample();
}

sge::mad::mpeg_file::channel_type
sge::mad::mpeg_file::channels() const
{
	return static_cast<channel_type>(2);
}

sge::mad::mpeg_file::sample_count
sge::mad::mpeg_file::sample_rate() const
{
	return sample_rate_;
}

sge::mad::mpeg_file::sample_count
sge::mad::mpeg_file::bits_per_sample() const
{
	return static_cast<sample_count>(16);
}

void sge::mad::mpeg_file::reset()
{
	s.reset();
	buffered_.clear();
}
