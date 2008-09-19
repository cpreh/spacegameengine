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
	typedef audio::sample_type sample_type;
	typedef audio::channel_type channel_type;
	typedef audio::raw_array_type raw_array_type;

	mpeg_file(path const &);

  sample_type read(sample_type samples, raw_array_type &);
  sample_type read_all(raw_array_type &);

  channel_type channels() const { return channels_; }
  sample_type sample_rate() const { return sample_rate_; }
  sample_type bits_per_sample() const { return static_cast<sample_type>(16); }
  void reset();
	private:
	sge::ifstream stdstream;
	stream s;
	frame f;
	synth syn;
	raw_array_type buffered_samples;
	channel_type channels_;
	sample_type sample_rate_;
};
}
}

#endif
