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


#include "../grab.hpp"
#include <awl/backends/x11/display.hpp>
#include <awl/backends/x11/window/instance.hpp>
#include <sge/input/exception.hpp>
#include <fcppt/assign/make_container.hpp>
#include <fcppt/function/object.hpp>
#include <fcppt/tr1/functional.hpp>
#include <fcppt/text.hpp>
#include <fcppt/time/sleep_any.hpp>
#include <fcppt/chrono/duration_impl.hpp>
#include <fcppt/chrono/milliseconds.hpp>
#include <X11/extensions/XInput2.h>

sge::x11input::cursor::grab::grab(
	awl::backends::x11::window::instance &_window,
	device::id const _id,
	cursor::image const _image
)
:
	window_(_window),
	id_(_id)
{
	XIEventMask mask =
	{
		id_.get(),
		0,
		0
	};

	for(
		;;
	)
	{
		switch(
			::XIGrabDevice(
				_window.display().get(),
				_id.get(),
				_window.get(),
				CurrentTime,
				_image.get(),
				GrabModeAsync,
				GrabModeAsync,
				True,
				&mask
			)
		)
		{
		case Success:
			return;
		case BadMatch:
		case BadWindow:
		case BadRequest:
			fcppt::time::sleep_any(
				fcppt::chrono::milliseconds(
					10
				)
			);
			break;
		default:
			throw sge::input::exception(
				FCPPT_TEXT("X11 grab failed!")
			);
		}
	}
}

sge::x11input::cursor::grab::~grab()
{
	::XIUngrabDevice(
		window_.display().get(),
		id_.get(),
		CurrentTime
	);
}
