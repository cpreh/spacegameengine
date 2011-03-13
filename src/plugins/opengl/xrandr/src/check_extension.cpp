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


#include "../check_extension.hpp"
#include <X11/Xlib.h>
#include <X11/extensions/Xrandr.h>
#include <sge/renderer/exception.hpp>
#include <awl/backends/x11/display.hpp>
#include <fcppt/text.hpp>

void
sge::opengl::xrandr::check_extension(
	awl::backends::x11::display &_display
)
{
	int event_base_return, error_base_return;

	if(
		::XRRQueryExtension(
			_display.get(),
			&event_base_return,
			&error_base_return
		)
		== False
	)
		throw sge::renderer::exception(
			FCPPT_TEXT("xrandr extension not present!")
		);
}
