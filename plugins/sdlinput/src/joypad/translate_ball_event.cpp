//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/input/joypad/axis_value.hpp>
#include <sge/input/joypad/shared_ptr.hpp>
#include <sge/input/joypad/event/relative_axis.hpp>
#include <sge/sdlinput/joypad/ball_direction.hpp>
#include <sge/sdlinput/joypad/device.hpp>
#include <sge/sdlinput/joypad/from_event.hpp>
#include <sge/sdlinput/joypad/map.hpp>
#include <sge/sdlinput/joypad/shared_ptr.hpp>
#include <sge/sdlinput/joypad/translate_ball_event.hpp>
#include <awl/event/base.hpp>
#include <awl/event/base_unique_ptr.hpp>
#include <awl/event/container.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/unique_ptr_to_base.hpp>
#include <fcppt/container/make.hpp>
#include <fcppt/optional/cat.hpp>
#include <fcppt/optional/make_if.hpp>
#include <fcppt/optional/object_impl.hpp>
#include <fcppt/config/external_begin.hpp>
#include <SDL_events.h>
#include <cstdint>
#include <vector>
#include <fcppt/config/external_end.hpp>


awl::event::container
sge::sdlinput::joypad::translate_ball_event(
	sge::sdlinput::joypad::map const &_joypads,
	SDL_JoyBallEvent const &_event
)
{
	sge::sdlinput::joypad::shared_ptr const joypad{
		sge::sdlinput::joypad::from_event(
			_joypads,
			_event
		)
	};

	auto const make_event(
		[
			&joypad,
			&_event
		](
			sge::sdlinput::joypad::ball_direction const _direction,
			std::int16_t const _value
		)
		->
		fcppt::optional::object<
			awl::event::base_unique_ptr
		>
		{
			return
				fcppt::optional::make_if(
					_value
					!=
					0,
					[
						&joypad,
						&_event,
						_direction,
						_value
					]{
						return
							fcppt::unique_ptr_to_base<
								awl::event::base
							>(
								fcppt::make_unique_ptr<
									sge::input::joypad::event::relative_axis
								>(
									sge::input::joypad::shared_ptr{
										joypad
									},
									joypad->ball_axis(
										_event.ball,
										_direction
									),
									sge::input::joypad::axis_value{
										_value
									}
								)
							);
					}
				);
		}
	);

	return
		fcppt::optional::cat<
			awl::event::container
		>(
			fcppt::container::make<
				std::vector<
					fcppt::optional::object<
						awl::event::base_unique_ptr
					>
				>
			>(
				make_event(
					sge::sdlinput::joypad::ball_direction::x,
					_event.xrel
				),
				make_event(
					sge::sdlinput::joypad::ball_direction::y,
					_event.yrel
				)
			)
		);
}
