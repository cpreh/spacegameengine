/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2016 Carl Philipp Reh (carlphilippreh <at> gmail.com)

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU Lesser General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
*/


#include <sge/wininput/cursor/define.hpp>
#include <awl/backends/windows/message_type.hpp>
#include <awl/backends/windows/windows.hpp>
#include <awl/backends/windows/window/event/callback.hpp>
#include <awl/backends/windows/window/event/object_fwd.hpp>
#include <awl/backends/windows/window/event/processor.hpp>
#include <awl/backends/windows/window/event/return_type.hpp>
#include <fcppt/strong_typedef_construct_cast.hpp>
#include <fcppt/cast/to_unsigned_fun.hpp>
#include <fcppt/optional/maybe_void.hpp>
#include <fcppt/optional/object_impl.hpp>
#include <fcppt/preprocessor/disable_vc_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>
#include <fcppt/signal/auto_connection.hpp>
#include <fcppt/config/external_begin.hpp>
#include <functional>
#include <fcppt/config/external_end.hpp>


FCPPT_PP_PUSH_WARNING
FCPPT_PP_DISABLE_VC_WARNING(4355)

sge::wininput::cursor::define::define(
	awl::backends::windows::window::event::processor &_processor
)
:
	previous_cursor_(),
	pixmap_(),

	connection_(
		_processor.register_callback(
			fcppt::strong_typedef_construct_cast<
				awl::backends::windows::message_type,
				fcppt::cast::to_unsigned_fun
			>(
				WM_SETCURSOR
			),
			awl::backends::windows::window::event::callback{
				std::bind(
					&wininput::cursor::define::on_cursor,
					this,
					std::placeholders::_1
				)
			}
		)
	)
{
}

FCPPT_PP_POP_WARNING

sge::wininput::cursor::define::~define()
{
	fcppt::optional::maybe_void(
		previous_cursor_,
		[](
			HCURSOR const _cursor
		)
		{
			::SetCursor(
				_cursor
			);
		}
	);
}

awl::backends::windows::window::event::return_type
sge::wininput::cursor::define::on_cursor(
	awl::backends::windows::window::event::object const &
)
{
	HCURSOR const old(
		::SetCursor(
			pixmap_.get()
		)
	);

	if(
		!previous_cursor_.has_value()
	)
		previous_cursor_ =
			optional_hcursor(
				old
			);

	return
		awl::backends::windows::window::event::return_type(
			TRUE
		);
}
