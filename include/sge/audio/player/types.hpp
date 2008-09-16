#ifndef SGE_AUDIO_PLAYER_TYPES_HPP_INCLUDED
#define SGE_AUDIO_PLAYER_TYPES_HPP_INCLUDED

#include "../../math/vector.hpp"



namespace sge
{
namespace audio
{
typedef math::vector3 sound_pos;

struct sound_angle
{
	math::vector3 forward,
	              up;
};
}
}

#endif
