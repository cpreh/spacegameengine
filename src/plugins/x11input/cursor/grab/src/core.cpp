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


#include "../core.hpp"
#include "../handle.hpp"
#include "../return_value.hpp"
#include "../return_value_set.hpp"
#include <awl/backends/x11/display.hpp>
#include <awl/backends/x11/window/instance.hpp>
#include <fcppt/assign/make_container.hpp>
#include <fcppt/function/object.hpp>
#include <fcppt/tr1/functional.hpp>
#include <X11/Xlib.h>

sge::x11input::cursor::grab::core::core(
	awl::backends::x11::window::instance &_window
)
:
	x11input::cursor::confine(),
	window_(_window)
{
	cursor::grab::handle(
		std::tr1::bind(
			::XGrabPointer,
			window_.display().get(),
			window_.get(),
			True,
			0u,
			GrabModeAsync,
			GrabModeAsync,
			window_.get(),
			None,
			CurrentTime
		),
		grab::return_value(
			GrabSuccess
		),
		fcppt::assign::make_container<
			cursor::grab::return_value_set
		>(
			grab::return_value(
				GrabFrozen
			)
		)
		(
			grab::return_value(
				AlreadyGrabbed
			)
		)
		(
			grab::return_value(
				GrabNotViewable
			)
		)
	);
}

sge::x11input::cursor::grab::core::~core()
{
	::XUngrabPointer(
		window_.display().get(),
		CurrentTime
	);
}
