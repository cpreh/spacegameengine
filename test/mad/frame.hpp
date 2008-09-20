#ifndef SGE_MAD_FRAME_HPP_INCLUDED
#define SGE_MAD_FRAME_HPP_INCLUDED

#include "frame_fwd.hpp"
#include <mad.h>
#include <sge/audio/types.hpp>
#include <boost/noncopyable.hpp>

namespace sge
{
namespace mad
{
class frame : boost::noncopyable
{
	public:
	frame();
	mad_frame &madframe() { return frame_; }
	mad_frame const &madframe() const { return frame_; }
	audio::sample_count sample_rate() const;
	audio::channel_type channels() const;
	string const info() const;
	audio::sample_container const synthesize();
	~frame();

	private:
	mad_frame frame_;
};
}
}

#endif
