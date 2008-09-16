#include "../listener_wrapper.hpp"
#include "../error.hpp"
#include "../openal.hpp"

sge::openal::listener_wrapper::listener_wrapper()
{
	set_pos(pos_);
	set_angle(angle_);
}

void sge::openal::listener_wrapper::set_pos(math::vector3 const &n)
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

void sge::openal::listener_wrapper::set_angle(audio::sound_angle const &n)
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

sge::math::vector3 const sge::openal::listener_wrapper::get_pos() const
{
	return pos_;
}

sge::audio::sound_angle const sge::openal::listener_wrapper::get_angle() const
{
	return angle_;
}
