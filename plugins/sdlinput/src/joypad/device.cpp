//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/input/info/id.hpp>
#include <sge/input/joypad/absolute_axis.hpp>
#include <sge/input/joypad/absolute_axis_id.hpp>
#include <sge/input/joypad/device.hpp>
#include <sge/input/joypad/info.hpp>
#include <sge/input/joypad/relative_axis.hpp>
#include <sge/input/joypad/relative_axis_id.hpp>
#include <sge/input/joypad/ff/effect.hpp>
#include <sge/input/joypad/ff/effect_unique_ptr.hpp>
#include <sge/input/joypad/ff/parameters_fwd.hpp>
#include <sge/sdlinput/joypad/ball_direction.hpp>
#include <sge/sdlinput/joypad/device_id.hpp>
#include <sge/sdlinput/joypad/device.hpp>
#include <sge/sdlinput/joypad/ff_effect.hpp>
#include <sge/sdlinput/joypad/hat_direction.hpp>
#include <sge/sdlinput/joypad/instance_id.hpp>
#include <sge/sdlinput/joypad/make_info.hpp>
#include <sge/sdlinput/joypad/num_axes.hpp>
#include <sge/sdlinput/joypad/num_balls.hpp>
#include <sge/sdlinput/joypad/num_hats.hpp>
#include <sge/window/object_fwd.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/unique_ptr_to_base.hpp>
#include <fcppt/assert/optional_error.hpp>
#include <fcppt/assert/unreachable.hpp>
#include <fcppt/container/at_optional.hpp>
#include <fcppt/config/external_begin.hpp>
#include <SDL_joystick.h>
#include <cstdint>
#include <fcppt/config/external_end.hpp>


sge::sdlinput::joypad::device::device(
	sge::window::object &_window,
	sge::sdlinput::joypad::device_id const _id
)
:
	sge::input::joypad::device{},
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

sge::input::joypad::absolute_axis
sge::sdlinput::joypad::device::axis(
	std::uint8_t const _id
) const
{
	sge::input::joypad::absolute_axis_id const axis_id{
		_id
	};

	return
		sge::input::joypad::absolute_axis{
			FCPPT_ASSERT_OPTIONAL_ERROR(
				fcppt::container::at_optional(
					this->info().absolute_axes(),
					axis_id
				)
			).get().code(),
			axis_id
		};
}

sge::input::joypad::relative_axis
sge::sdlinput::joypad::device::ball_axis(
	std::uint8_t const _id,
	sge::sdlinput::joypad::ball_direction const _direction
) const
{
	auto const ball_mult(
		[
			_direction
		]()
		->
		sge::input::info::id
		{
			switch(
				_direction
			)
			{
			case sge::sdlinput::joypad::ball_direction::x:
				return
					0u;
			case sge::sdlinput::joypad::ball_direction::y:
				return
					1u;
			}

			FCPPT_ASSERT_UNREACHABLE;
		}
	);

	sge::input::joypad::relative_axis_id const axis_id{
		_id
		+
		sge::sdlinput::joypad::num_balls(
			this->instance_.get()
		)
		*
		ball_mult()
	};

	return
		sge::input::joypad::relative_axis{
			FCPPT_ASSERT_OPTIONAL_ERROR(
				fcppt::container::at_optional(
					this->info().relative_axes(),
					axis_id
				)
			).get().code(),
			axis_id
		};
}

sge::input::joypad::absolute_axis
sge::sdlinput::joypad::device::hat_axis(
	std::uint8_t const _id,
	sge::sdlinput::joypad::hat_direction const _direction
) const
{
	auto const hat_mult(
		[
			_direction
		]()
		->
		sge::input::info::id
		{
			switch(
				_direction
			)
			{
			case sge::sdlinput::joypad::hat_direction::x:
				return
					0u;
			case sge::sdlinput::joypad::hat_direction::y:
				return
					1u;
			}

			FCPPT_ASSERT_UNREACHABLE;
		}
	);

	sge::input::joypad::absolute_axis_id const axis_id{
		sge::sdlinput::joypad::num_axes(
			this->instance_.get()
		)
		+
		_id
		+
		sge::sdlinput::joypad::num_hats(
			this->instance_.get()
		)
		*
		hat_mult()
	};

	return
		sge::input::joypad::absolute_axis{
			FCPPT_ASSERT_OPTIONAL_ERROR(
				fcppt::container::at_optional(
					this->info().absolute_axes(),
					axis_id
				)
			).get().code(),
			axis_id
		};
}
