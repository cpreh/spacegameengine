#include "../listener.hpp"
#include "../error.hpp"
#include "../openal.hpp"

void sge::openal::listener::pos(audio::point const &n)
{
	pos_ = n;
	// OpenAL wants float
	float const vec[3] = 
		{ 
			static_cast<float>(n.x()),
			static_cast<float>(n.y()),
			static_cast<float>(n.z()) 
		};
	alListenerfv(AL_POSITION, vec); SGE_OPENAL_ERROR_CHECK;
}

void sge::openal::listener::direction(audio::angle const &n)
{
	float const vec[6] = 
		{ 
			static_cast<float>(n.forward.x()),
			static_cast<float>(n.forward.y()),
			static_cast<float>(n.forward.z()),
			static_cast<float>(n.up.x()),
			static_cast<float>(n.up.y()),
			static_cast<float>(n.up.z()) 
		};

	alListenerfv(AL_POSITION, vec); SGE_OPENAL_ERROR_CHECK;
}

sge::audio::point const sge::openal::listener::pos() const
{
	return pos_;
}

sge::audio::angle const sge::openal::listener::direction() const
{
	return angle_;
}
