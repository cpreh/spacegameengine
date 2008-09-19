#ifndef SGE_OPENAL_LISTENER_WRAPPER_HPP_INCLUDED
#define SGE_OPENAL_LISTENER_WRAPPER_HPP_INCLUDED

#include <sge/math/vector.hpp>
#include <sge/audio/types.hpp>

namespace sge
{
namespace openal
{
class listener_wrapper
{
	public:
	listener_wrapper();
	void set_pos(audio::sound_pos const &);
	audio::sound_pos const get_pos() const;
	void set_angle(audio::sound_angle const &);
	audio::sound_angle const get_angle() const;
	private:
	audio::sound_pos pos_;
	audio::sound_angle angle_;
};
}
}

#endif
