//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/window/object_ref.hpp>
#include <sge/wlinput/xkb_context_ref.hpp>
#include <sge/wlinput/focus/create.hpp>
#include <sge/wlinput/focus/create_function.hpp>
#include <sge/wlinput/focus/object.hpp>
#include <awl/backends/wayland/seat_ref.hpp>
#include <awl/backends/wayland/window/object_ref.hpp>
#include <awl/event/container_reference.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/log/object_reference.hpp>


sge::wlinput::focus::create_function
sge::wlinput::focus::create(
	fcppt::log::object_reference const _log,
	sge::window::object_ref const _sge_window,
	sge::wlinput::xkb_context_ref const _context,
	awl::backends::wayland::window::object_ref const _window,
	awl::event::container_reference const _events
)
{
	return
		sge::wlinput::focus::create_function{
			[
				_log,
				_sge_window,
				_context,
				_window,
				_events
			](
				awl::backends::wayland::seat_ref const _seat
			)
			{
				return
					fcppt::make_unique_ptr<
						sge::wlinput::focus::object
					>(
						_log,
						_sge_window,
						_context,
						_window,
						_events,
						_seat
					);
			}
		};
}
