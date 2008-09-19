#ifndef SGE_MAD_SYNTH_HPP_INCLUDED
#define SGE_MAD_SYNTH_HPP_INCLUDED

#include <mad.h>
#include <sge/audio/types.hpp>

namespace sge
{
namespace mad
{
class frame;

class synth
{
	public:
	synth();
	void synthesize(frame&,audio::raw_array_type &,audio::channel_type);
	mad_synth &madsynth() { return synth_; }
	mad_synth const &madsynth() const { return synth_; }
	~synth();

	private:
	mad_synth synth_;
};
}
}

#endif
