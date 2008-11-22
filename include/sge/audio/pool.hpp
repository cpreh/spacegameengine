#ifndef SGE_AUDIO_POOL_HPP_INCLUDED
#define SGE_AUDIO_POOL_HPP_INCLUDED

#include "sound_fwd.hpp"
#include "../export.hpp"

namespace sge
{
namespace audio
{
class pool
{
	public:
	virtual void add(sound_ptr,bool continue_playing = true) = 0;
	virtual void update() = 0;
	virtual bool sounds_finished() const = 0;
	SGE_SYMBOL virtual ~pool();
};

}
}

#endif
