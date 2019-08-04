//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/input/joypad/device.hpp>
#include <sge/input/joypad/ff/effect.hpp>
#include <sge/input/joypad/ff/effect_unique_ptr.hpp>
#include <sge/input/joypad/ff/parameters_fwd.hpp>
#include <sge/sdlinput/joypad/device_id.hpp>
#include <sge/sdlinput/joypad/device.hpp>
#include <sge/sdlinput/joypad/ff_effect.hpp>
#include <sge/sdlinput/joypad/instance_id.hpp>
#include <sge/sdlinput/joypad/make_info.hpp>
#include <sge/window/object_fwd.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/unique_ptr_to_base.hpp>
#include <fcppt/config/external_begin.hpp>
#include <SDL_joystick.h>
#include <fcppt/config/external_end.hpp>


sge::sdlinput::joypad::device::device(
	sge::window::object &_window,
	sge::sdlinput::joypad::device_id const _id
)
:
	instance_{
		_id
	},
	window_{
		_window
	},
	info_{
		sge::sdlinput::joypad::make_info(
			instance_.get()
		)
	}
{
}

sge::sdlinput::joypad::device::~device()
{
}

sge::window::object &
sge::sdlinput::joypad::device::window() const
{
	return
		this->window_;
}

sge::input::joypad::info const &
sge::sdlinput::joypad::device::info() const
{
	return
		this->info_;
}

sge::input::joypad::ff::effect_unique_ptr
sge::sdlinput::joypad::device::create_ff_effect(
	sge::input::joypad::ff::parameters const &_parameters
)
{
	return
		fcppt::unique_ptr_to_base<
			sge::input::joypad::ff::effect
		>(
			fcppt::make_unique_ptr<
				sge::sdlinput::joypad::ff_effect
			>(
				this->instance_.get(),
				_parameters
			)
		);
}

SDL_JoystickID
sge::sdlinput::joypad::device::id() const
{
	return
		sge::sdlinput::joypad::instance_id(
			this->instance_.get()
		);
}
