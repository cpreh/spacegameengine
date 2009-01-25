#ifndef SGE_MAD_FRAME_HPP_INCLUDED
#define SGE_MAD_FRAME_HPP_INCLUDED

#include "synth.hpp"
#include <mad.h>
#include <sge/audio/types.hpp>
#include <sge/string.hpp>
#include <boost/noncopyable.hpp>

namespace sge
{
namespace mad
{
class frame : boost::noncopyable
{
	public:
	frame();
	mad_frame &madframe();
	audio::sample_count sample_rate() const;
	audio::channel_type channels() const;
	unsigned layer() const;
	string const info() const;
	audio::sample_container const synthesize();
	~frame();

	private:
	mad_frame frame_;
	synth syn;
};
}
}

#endif
