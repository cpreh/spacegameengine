/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2012 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#include <sge/opengl/config.hpp>
#ifdef SGE_OPENGL_HAVE_XF86VMODE
#include <sge/opengl/x11/resolution/xf86_vmode.hpp>
#include <sge/opengl/xf86vmode/choose_mode.hpp>
#include <sge/renderer/display_mode.hpp>

sge::opengl::x11::resolution::xf86_vmode::xf86_vmode(
	renderer::display_mode const &_mode,
	awl::backends::x11::display &_display,
	awl::backends::x11::screen const _screen
)
:
	modes_(
		_display,
		_screen
	),
	resolution_(
		xf86vmode::choose_mode(
			_mode,
			modes_
		)
	)
{}

sge::opengl::x11::resolution::xf86_vmode::~xf86_vmode()
{
}
#endif
