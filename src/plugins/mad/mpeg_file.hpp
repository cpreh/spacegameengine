#ifndef SGE_MAD_MPEG_FILE_HPP_INCLUDED
#define SGE_MAD_MPEG_FILE_HPP_INCLUDED

#include <sge/path.hpp>
#include <sge/fstream.hpp>
#include <sge/audio/file.hpp>
#include "stream.hpp"
#include "synth.hpp"
#include "frame.hpp"

namespace sge
{
namespace mad
{
class mpeg_file : public audio::file
{
	public:
	typedef audio::sample_count sample_count;
	typedef audio::channel_type channel_type;
	typedef audio::sample_container sample_container;

	explicit mpeg_file(path const &);

	sample_count read(sample_count samples, sample_container &);
	sample_count read_all(sample_container &);

	channel_type channels() const { return static_cast<channel_type>(2); }
	sample_count sample_rate() const { return sample_rate_; }
	sample_count bits_per_sample() const { return static_cast<sample_count>(16); }
	void reset();
	private:
	sge::ifstream stdstream;
	stream s;
	sample_container buffered_;
	sample_count sample_rate_;
};
}
}

#endif
