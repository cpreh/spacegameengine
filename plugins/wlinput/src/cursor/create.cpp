//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/window/object_fwd.hpp>
#include <sge/wlinput/cursor/create.hpp>
#include <sge/wlinput/cursor/create_function.hpp>
#include <sge/wlinput/cursor/object.hpp>
#include <awl/backends/wayland/seat_fwd.hpp>
#include <awl/backends/wayland/window/object_fwd.hpp>
#include <awl/event/container_reference.hpp>
#include <fcppt/make_unique_ptr.hpp>


sge::wlinput::cursor::create_function
sge::wlinput::cursor::create(
	sge::window::object &_sge_window,
	awl::backends::wayland::window::object const &_window,
	awl::event::container_reference const _events
)
{
	return
		sge::wlinput::cursor::create_function{
			[
				&_sge_window,
				&_window,
				_events
			](
				awl::backends::wayland::seat const &_seat
			)
			{
				return
					fcppt::make_unique_ptr<
						sge::wlinput::cursor::object
					>(
						_sge_window,
						_window,
						_events,
						_seat
					);
			}
		};
}
