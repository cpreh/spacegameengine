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


#include "../xi2.hpp"
#include <sge/x11input/config.hpp>

#if defined(SGE_X11INPUT_HAVE_XI_2_1)
#include "../handle.hpp"
#include "../return_value.hpp"
#include "../return_value_set.hpp"
#include <awl/backends/x11/display.hpp>
#include <awl/backends/x11/window/instance.hpp>
#include <fcppt/assign/make_container.hpp>
#include <fcppt/function/object.hpp>
#include <fcppt/tr1/functional.hpp>
#include <X11/extensions/XInput2.h>

sge::x11input::cursor::grab::xi2::xi2(
	awl::backends::x11::window::instance &_window,
	device::id const _id
)
:
	window_(_window),
	id_(_id)
{
	unsigned char raw_data[4] = {0};

	XISetMask(
		raw_data,
		XI_Motion
	);

	XISetMask(
		raw_data,
		XI_ButtonPress
	);

	XISetMask(
		raw_data,
		XI_ButtonRelease
	);

	XIEventMask mask =
	{
		id_.get(),
		4,
		raw_data
	};

	cursor::grab::handle(
		std::tr1::bind(
			::XIGrabDeviceWithConfine,
			_window.display().get(),
			_id.get(),
			_window.get(),
			_window.get(),
			CurrentTime,
			None,
			GrabModeAsync,
			GrabModeAsync,
			True,
			&mask
		),
		grab::return_value(
			Success
		),
		fcppt::assign::make_container<
			cursor::grab::return_value_set
		>(
			grab::return_value(
				BadMatch
			)
		)
		(
			grab::return_value(
				BadWindow
			)
		)
	);
}

sge::x11input::cursor::grab::xi2::~xi2()
{
	::XIUngrabDevice(
		window_.display().get(),
		id_.get(),
		CurrentTime
	);
}

#endif
