//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/input/exception.hpp>
#include <sge/x11input/cursor/create_grab.hpp>
#include <sge/x11input/cursor/grab.hpp>
#include <sge/x11input/cursor/optional_grab_unique_ptr.hpp>
#include <sge/x11input/device/id.hpp>
#include <awl/backends/x11/cursor/object_fwd.hpp>
#include <awl/backends/x11/window/base_fwd.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/log/error.hpp>
#include <fcppt/log/object_fwd.hpp>
#include <fcppt/log/out.hpp>


sge::x11input::cursor::optional_grab_unique_ptr
sge::x11input::cursor::create_grab(
	fcppt::log::object &_log,
	awl::backends::x11::window::base const &_window,
	sge::x11input::device::id const _id,
	awl::backends::x11::cursor::object const &_cursor
)
try
{
	return
		sge::x11input::cursor::optional_grab_unique_ptr{
			fcppt::make_unique_ptr<
				sge::x11input::cursor::grab
			>(
				_window,
				_id,
				_cursor
			)
		};
}
catch(
	sge::input::exception const &_error
)
{
	FCPPT_LOG_ERROR(
		_log,
		fcppt::log::out
			<<
			_error.string()
	)

	return
		sge::x11input::cursor::optional_grab_unique_ptr{};
}
