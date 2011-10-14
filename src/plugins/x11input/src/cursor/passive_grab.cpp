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


#include <sge/x11input/cursor/passive_grab.hpp>
#include <sge/x11input/cursor/image.hpp>
#include <sge/x11input/device/id.hpp>
#include <sge/input/exception.hpp>
#include <fcppt/text.hpp>
#include <awl/backends/x11/display.hpp>
#include <awl/backends/x11/window/instance.hpp>
#include <fcppt/config/external_begin.hpp>
#include <X11/extensions/XInput2.h>
#include <fcppt/config/external_end.hpp>

#include <iostream>

namespace
{

XIGrabModifiers const
initial_modifiers =
{
	0,
	0
};

}

sge::x11input::cursor::passive_grab::passive_grab(
	awl::backends::x11::window::instance &_window,
	device::id const _id,
	cursor::image const _image
)
:
	window_(_window),
	id_(_id),
	num_modifiers_(
		0
	),
	modifiers_(
		initial_modifiers
	)
{
	XIEventMask mask =
	{
		id_.get(),
		0,
		0
	};

	if(
		::XIGrabFocusIn(
			_window.display().get(),
			_id.get(),
			_window.get(),
			GrabModeAsync,
			GrabModeAsync,
			True,
			&mask,
			num_modifiers_,
			&modifiers_
		)
		== -1
	)
		throw sge::input::exception(
			FCPPT_TEXT("XIGrabFocusIn() failed!")
		);

	std::cout << "foobar\n";
}

sge::x11input::cursor::passive_grab::~passive_grab()
{
	::XIUngrabFocusIn(
		window_.display().get(),
		id_.get(),
		window_.get(),
		num_modifiers_,
		&modifiers_
	);
}
