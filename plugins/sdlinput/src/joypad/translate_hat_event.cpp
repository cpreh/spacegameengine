//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/input/joypad/axis_value.hpp>
#include <sge/input/joypad/shared_ptr.hpp>
#include <sge/input/joypad/event/absolute_axis.hpp>
#include <sge/sdlinput/joypad/device.hpp>
#include <sge/sdlinput/joypad/from_event.hpp>
#include <sge/sdlinput/joypad/hat_direction.hpp>
#include <sge/sdlinput/joypad/map.hpp>
#include <sge/sdlinput/joypad/shared_ptr.hpp>
#include <sge/sdlinput/joypad/translate_hat_event.hpp>
#include <awl/event/base.hpp>
#include <awl/event/base_unique_ptr.hpp>
#include <awl/event/container.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/unique_ptr_to_base.hpp>
#include <fcppt/assert/unreachable.hpp>
#include <fcppt/container/make.hpp>
#include <fcppt/config/external_begin.hpp>
#include <SDL_events.h>
#include <SDL_joystick.h>
#include <cstdint>
#include <utility>
#include <fcppt/config/external_end.hpp>


namespace
{

typedef
std::pair<
	sge::input::joypad::axis_value,
	sge::input::joypad::axis_value
>
axes_direction;

axes_direction
axes_values(
	std::uint8_t const _value
)
{
	switch(
		_value
	)
	{
	case SDL_HAT_LEFTUP:
		return
			axes_direction{
				-1,
				-1
			};
	case SDL_HAT_UP:
		return
			axes_direction{
				0,
				-1
			};
	case SDL_HAT_RIGHTUP:
		return
			axes_direction{
				1,
				-1
			};
	case SDL_HAT_LEFT:
		return
			axes_direction{
				-1,
				0
			};
	case SDL_HAT_CENTERED:
		return
			axes_direction{
				0,
				0
			};
	case SDL_HAT_RIGHT:
		return
			axes_direction{
				1,
				0
			};
	case SDL_HAT_LEFTDOWN:
		return
			axes_direction{
				-1,
				1
			};
	case SDL_HAT_DOWN:
		return
			axes_direction{
				0,
				1
			};
	case SDL_HAT_RIGHTDOWN:
		return
			axes_direction{
				1,
				1
			};
	}

	FCPPT_ASSERT_UNREACHABLE;
}

}


awl::event::container
sge::sdlinput::joypad::translate_hat_event(
	sge::sdlinput::joypad::map const &_joypads,
	SDL_JoyHatEvent const &_event
)
{
	sge::sdlinput::joypad::shared_ptr const joypad{
		sge::sdlinput::joypad::from_event(
			_joypads,
			_event
		)
	};

	axes_direction const axes{
		axes_values(
			_event.value
		)
	};

	auto const make_event(
		[
			&joypad,
			&_event
		](
			sge::sdlinput::joypad::hat_direction const _direction,
			sge::input::joypad::axis_value const _value
		)
		->
		awl::event::base_unique_ptr
		{
			return
				fcppt::unique_ptr_to_base<
					awl::event::base
				>(
					fcppt::make_unique_ptr<
						sge::input::joypad::event::absolute_axis
					>(
						sge::input::joypad::shared_ptr{
							joypad
						},
						joypad->hat_axis(
							_event.hat,
							_direction
						),
						_value
					)
				);
		}
	);

	return
		fcppt::container::make<
			awl::event::container
		>(
			make_event(
				sge::sdlinput::joypad::hat_direction::x,
				axes.first
			),
			make_event(
				sge::sdlinput::joypad::hat_direction::y,
				axes.second
			)
		);
}
