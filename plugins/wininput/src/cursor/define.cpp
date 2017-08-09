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


#include <sge/window/event_function.hpp>
#include <sge/window/object.hpp>
#include <sge/wininput/cursor/define.hpp>
#include <awl/backends/windows/windows.hpp>
#include <awl/backends/windows/window/event/generic.hpp>
#include <awl/event/base.hpp>
#include <awl/event/container.hpp>
#include <awl/window/event/base.hpp>
#include <fcppt/reference_impl.hpp>
#include <fcppt/cast/dynamic.hpp>
#include <fcppt/optional/maybe_void.hpp>
#include <fcppt/optional/object_impl.hpp>
#include <fcppt/preprocessor/disable_vc_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>


FCPPT_PP_PUSH_WARNING
FCPPT_PP_DISABLE_VC_WARNING(4355)

sge::wininput::cursor::define::define(
	sge::window::object &_window
)
:
	previous_cursor_{},
	pixmap_{},
	connection_{
		_window.event_handler(
			sge::window::event_function{
				[
					this
				](
					awl::window::event::base const &_event
				){
					return
						this->on_event(
							_event
						);
				}
			}
		)
	}
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

awl::event::container
sge::wininput::cursor::define::on_event(
	awl::window::event::base const &_event
)
{
	fcppt::optional::maybe_void(
		fcppt::cast::dynamic<
			awl::backends::windows::window::event::generic const
		>(
			_event
		),
		[
			this
		](
			fcppt::reference<
				awl::backends::windows::window::event::generic const
			> const _window_event
		)
		{
			if(
				_window_event.get().type().get()
				==
				WM_SETCURSOR
			)
				this->on_cursor();
		}
	);

	return
		awl::event::container{};
}

void
sge::wininput::cursor::define::on_cursor()
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
}
