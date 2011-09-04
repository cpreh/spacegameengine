/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2011 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#include "../define.hpp"
#include <awl/backends/windows/windows.hpp>
#include <awl/backends/windows/window/event/processor.hpp>
#include <fcppt/preprocessor/disable_vc_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>
#include <fcppt/tr1/functional.hpp>
#include <fcppt/optional_impl.hpp>

sge::dinput::cursor::define::define(
	awl::backends::windows::window::event::processor &_processor
)
:
	previous_cursor_(),
	pixmap_(),
FCPPT_PP_PUSH_WARNING
FCPPT_PP_DISABLE_VC_WARNING(4355)
	connection_(
		_processor.register_callback(
			WM_SETCURSOR,
			std::tr1::bind(
				&dinput::cursor::define::on_cursor,
				this,
				std::tr1::placeholders::_1
			)
		)
	)
FCPPT_PP_POP_WARNING
{
}

sge::dinput::cursor::define::~define()
{
	if(
		previous_cursor_
	)
		::SetCursor(
			*previous_cursor_
		);
}

awl::backends::windows::window::event::return_type
sge::dinput::cursor::define::on_cursor(
	awl::backends::windows::window::event::object const &
)
{
	HCURSOR const old(
		::SetCursor(
			pixmap_.get()
		)
	);

	if(
		!previous_cursor_
	)
		previous_cursor_ = old;

	return
		awl::backends::windows::window::event::return_type(
			TRUE
		);
}
