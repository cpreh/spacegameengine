//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_SDLINPUT_JOYPAD_INSTANCE_HPP_INCLUDED
#define SGE_SDLINPUT_JOYPAD_INSTANCE_HPP_INCLUDED

#include <sge/sdlinput/joypad/device_id.hpp>
#include <fcppt/nonmovable.hpp>
#include <fcppt/config/external_begin.hpp>
#include <SDL_joystick.h>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace sdlinput
{
namespace joypad
{

class instance
{
	FCPPT_NONMOVABLE(
		instance
	);
public:
	explicit
	instance(
		sge::sdlinput::joypad::device_id
	);

	~instance();

	[[nodiscard]]
	SDL_Joystick &
	get() const;
private:
	SDL_Joystick *const impl_;
};

}
}
}

#endif
