//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/input/joypad/shared_ptr.hpp>
#include <sge/input/joypad/event/discover.hpp>
#include <sge/sdlinput/joypad/device.hpp>
#include <sge/sdlinput/joypad/device_id.hpp>
#include <sge/sdlinput/joypad/discover.hpp>
#include <sge/sdlinput/joypad/map.hpp>
#include <sge/sdlinput/joypad/shared_ptr.hpp>
#include <sge/window/object_fwd.hpp>
#include <awl/event/base.hpp>
#include <awl/event/container.hpp>
#include <fcppt/make_shared_ptr.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/reference_impl.hpp>
#include <fcppt/unique_ptr_to_base.hpp>
#include <fcppt/container/insert.hpp>
#include <fcppt/container/make.hpp>
#include <fcppt/config/external_begin.hpp>
#include <SDL_events.h>
#include <fcppt/config/external_end.hpp>


awl::event::container
sge::sdlinput::joypad::discover(
	fcppt::reference<
		sge::sdlinput::joypad::map
	> const _joypads,
	sge::window::object &_window,
	SDL_JoyDeviceEvent const &_event
)
{
	sge::sdlinput::joypad::shared_ptr const result{
		fcppt::make_shared_ptr<
			sge::sdlinput::joypad::device
		>(
			_window,
			sge::sdlinput::joypad::device_id{
				_event.which
			}
		)
	};

	return
		fcppt::container::insert(
			_joypads.get(),
			sge::sdlinput::joypad::map::value_type{
				result->id(),
				result
			}
		)
		?
			fcppt::container::make<
				awl::event::container
			>(
				fcppt::unique_ptr_to_base<
					awl::event::base
				>(
					fcppt::make_unique_ptr<
						sge::input::joypad::event::discover
					>(
						sge::input::joypad::shared_ptr{
							result
						}
					)
				)
			)
		:
			awl::event::container{}
		;
}
