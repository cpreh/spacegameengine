//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_SDLINPUT_JOYPAD_DEVICE_HPP_INCLUDED
#define SGE_SDLINPUT_JOYPAD_DEVICE_HPP_INCLUDED

#include <sge/input/joypad/device.hpp>
#include <sge/input/joypad/info.hpp>
#include <sge/input/joypad/ff/effect_unique_ptr.hpp>
#include <sge/input/joypad/ff/parameters_fwd.hpp>
#include <sge/sdlinput/joypad/device_id.hpp>
#include <sge/sdlinput/joypad/device_fwd.hpp>
#include <sge/sdlinput/joypad/instance.hpp>
#include <sge/window/object_fwd.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/config/external_begin.hpp>
#include <SDL_joystick.h>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace sdlinput
{
namespace joypad
{

class device
:
	public
		sge::input::joypad::device
{
	FCPPT_NONCOPYABLE(
		device
	);
public:
	device(
		sge::window::object &,
		sge::sdlinput::joypad::device_id
	);

	~device()
	override;

	sge::window::object &
	window() const
	override;

	sge::input::joypad::info const &
	info() const
	override;

	sge::input::joypad::ff::effect_unique_ptr
	create_ff_effect(
		sge::input::joypad::ff::parameters const &
	)
	override;

	SDL_JoystickID
	id() const;
private:
	sge::sdlinput::joypad::instance const instance_;

	sge::window::object &window_;

	sge::input::joypad::info const info_;
};

}
}
}

#endif
