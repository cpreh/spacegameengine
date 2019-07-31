//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/window/object_fwd.hpp>
#include <sge/wlinput/xkb_context_fwd.hpp>
#include <sge/wlinput/focus/create.hpp>
#include <sge/wlinput/focus/create_function.hpp>
#include <sge/wlinput/focus/object.hpp>
#include <awl/backends/wayland/seat_fwd.hpp>
#include <awl/backends/wayland/window/object_fwd.hpp>
#include <awl/event/container_reference.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/log/object_fwd.hpp>


sge::wlinput::focus::create_function
sge::wlinput::focus::create(
	fcppt::log::object &_log,
	sge::window::object &_sge_window,
	sge::wlinput::xkb_context const &_context,
	awl::backends::wayland::window::object const &_window,
	awl::event::container_reference const _events
)
{
	return
		sge::wlinput::focus::create_function{
			[
				&_log,
				&_sge_window,
				&_context,
				&_window,
				_events
			](
				awl::backends::wayland::seat const &_seat
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
