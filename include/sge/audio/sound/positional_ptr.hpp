#ifndef SGE_AUDIO_SOUND_POSITIONAL_PTR_HPP_INCLUDED
#define SGE_AUDIO_SOUND_POSITIONAL_PTR_HPP_INCLUDED

#include <sge/audio/sound/positional_fwd.hpp>
#include <fcppt/shared_ptr.hpp>

namespace sge
{
namespace audio
{
namespace sound
{
typedef
fcppt::shared_ptr<positional>
positional_ptr;
}
}
}

#endif