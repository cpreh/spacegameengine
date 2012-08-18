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


#include <sge/opengl/x11/resolution/object.hpp>
#include <sge/opengl/x11/resolution/xrandr_mode.hpp>
#include <sge/opengl/xrandr/choose_resolution.hpp>
#include <sge/opengl/xrandr/resolution.hpp>
#include <sge/renderer/display_mode/object_fwd.hpp>
#include <awl/backends/x11/window/object_fwd.hpp>


sge::opengl::x11::resolution::xrandr_mode::xrandr_mode(
	sge::renderer::display_mode::object const &_mode,
	awl::backends::x11::window::object &_window
)
:
	sge::opengl::x11::resolution::object(),
	resolution_(
		sge::opengl::xrandr::choose_resolution(
			_window,
			_mode
		)
	)
{
}

sge::opengl::x11::resolution::xrandr_mode::~xrandr_mode()
{
}
