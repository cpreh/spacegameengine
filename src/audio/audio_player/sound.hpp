#ifndef SGE_SOUND_HPP_INCLUDED
#define SGE_SOUND_HPP_INCLUDED

namespace sge
{
struct sound
{
	enum sound_status { status_loaded,status_stopped,status_playing,status_paused };

	virtual void play(const bool) = 0;
	virtual void toggle_pause() = 0;
	virtual sound_status status() const = 0;
	virtual void stop() = 0;
	virtual void update() = 0;
};
}

#endif // SOUND_HPP
