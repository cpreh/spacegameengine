#ifndef SGE_SOUND_HPP_INCLUDED
#define SGE_SOUND_HPP_INCLUDED

#include "../../math/vector.hpp"

namespace sge
{
struct sound
{
	enum sound_status 
	{ 
		status_stopped,
		status_playing,
		status_paused 
	};

	virtual void play(const bool) = 0;
	virtual void toggle_pause() = 0;
	virtual sound_status status() const = 0;
	virtual void stop() = 0;
	virtual math::vector3 pos() const = 0;
	virtual void pos(const math::vector3 &) = 0;
	virtual bool positional() const;
	virtual void positional(const bool);
	virtual void update() {}
	virtual ~sound() {}
};
}

#endif // SOUND_HPP
