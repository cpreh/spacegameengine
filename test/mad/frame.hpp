#ifndef SGE_MAD_FRAME_HPP_INCLUDED
#define SGE_MAD_FRAME_HPP_INCLUDED

#include <mad.h>
#include <sge/audio/types.hpp>

namespace sge
{
namespace mad
{
class frame
{
	public:
	frame();
	mad_frame &madframe() { return frame_; }
	mad_frame const &madframe() const { return frame_; }
	audio::sample_type sample_rate() const;
	audio::channel_type channels() const;
	string const info() const;
	~frame();

	private:
	mad_frame frame_;
};
}
}

#endif
