#ifndef SGE_OPENAL_LISTENER_WRAPPER_HPP_INCLUDED
#define SGE_OPENAL_LISTENER_WRAPPER_HPP_INCLUDED

#include <sge/math/vector.hpp>
#include <sge/audio/player/sound_angle.hpp>

namespace sge
{
namespace openal
{
class listener_wrapper
{
	public:
	listener_wrapper();
	void set_pos(math::vector3 const &);
	math::vector3 const get_pos() const;
	void set_angle(audio::sound_angle const &);
	audio::sound_angle const get_angle() const;
	private:
	math::vector3 pos_;
	audio::sound_angle angle_;
};
}
}

#endif
