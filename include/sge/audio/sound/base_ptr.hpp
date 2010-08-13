#ifndef SGE_AUDIO_SOUND_BASE_PTR_HPP_INCLUDED
#define SGE_AUDIO_SOUND_BASE_PTR_HPP_INCLUDED

#include <sge/audio/sound/base_fwd.hpp>
#include <fcppt/shared_ptr.hpp>

namespace sge
{
namespace audio
{
namespace sound
{
typedef
fcppt::shared_ptr<base>
base_ptr;
}
}
}

#endif