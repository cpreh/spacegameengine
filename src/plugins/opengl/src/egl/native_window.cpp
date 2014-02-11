/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2013 Carl Philipp Reh (sefi@s-e-f-i.de)

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
#include <sge/opengl/egl/native_window.hpp>
#include <awl/window/object.hpp>
#include <fcppt/cast/static_downcast.hpp>
#include <fcppt/config/external_begin.hpp>
#include <EGL/egl.h>
#include <fcppt/config/external_end.hpp>
#if defined(SGE_OPENGL_HAVE_X11)
#include <awl/backends/x11/window/object.hpp>
#elif defined(FCPPT_CONFIG_WINDOWS_PLATFORM)
#include <awl/backends/windows/window/object.hpp>
#else
#error "Implement me!"
#endif


EGLNativeWindowType
sge::opengl::egl::native_window(
	awl::window::object &_window
)
{
#if defined(SGE_OPENGL_HAVE_X11)
	return
		fcppt::cast::static_downcast<
			awl::backends::x11::window::object &
		>(
			_window
		).get();
#elif defined(FCPPT_CONFIG_WINDOWS_PLATFORM)
	return
		fcppt::cast::static_downcast<
			awl::backends::windows::window::object &
		>(
			_window
		).hwnd();
#else
#error "Implement me!"
#endif
}
