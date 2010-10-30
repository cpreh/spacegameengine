/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2010 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#include "../system.hpp"
#include "../processor.hpp"
#include <X11/Xlib.h>
#include <X11/extensions/XInput2.h>
#include <sge/window/instance.hpp>
#include <sge/exception.hpp>
#include <awl/backends/x11/display.hpp>
#include <awl/backends/x11/window_instance.hpp>
#include <fcppt/make_shared_ptr.hpp>
#include <fcppt/polymorphic_pointer_cast.hpp>
#include <fcppt/text.hpp>

sge::x11input::system::system()
{
}

sge::x11input::system::~system()
{
}

sge::input::processor_ptr const
sge::x11input::system::create_processor(
	sge::window::instance_ptr const _window
)
{
	awl::backends::x11::window_instance_ptr const x11_window(
		fcppt::polymorphic_pointer_cast<
			awl::backends::x11::window_instance
		>(
			_window->awl_instance()
		)
	);

	// check if XInput 2 is available
	Display *const display(
		x11_window->display()->get()
	);

	int opcode, event, error;

	if(
		!::XQueryExtension(
			display,
			"XInputExtension",
			&opcode,
			&event,
			&error
		)
	)
		throw sge::exception(
			FCPPT_TEXT("X Input extension not available!")
		);

	int major = 2, minor = 0;

	if(
		::XIQueryVersion(
			display,
			&major,
			&minor
		)
		== BadRequest
	)
		throw sge::exception(
			FCPPT_TEXT("X Input extension is not version 2 or later!")
		);

	return
		fcppt::make_shared_ptr<
			x11input::processor
		>(
			_window
		);
}
