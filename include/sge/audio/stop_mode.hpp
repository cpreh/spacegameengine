#ifndef SGE_AUDIO_STOP_MODE_HPP_INCLUDED
#define SGE_AUDIO_STOP_MODE_HPP_INCLUDED

namespace sge
{
namespace audio
{
namespace stop_mode
{
enum type
{
	stop_playing,     // stop and erase as soon as the sound is dead
	continue_playing, // continue playing until pool is destroyed
	play_once         // when dead, play once more and then kill
};
}
}
}

#endif
