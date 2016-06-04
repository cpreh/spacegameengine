/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2016 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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


#include <fcppt/config/external_begin.hpp>
#include <wayland-egl-core.h>
#include <fcppt/config/external_end.hpp>
#include <sge/opengl/egl/surface.hpp>
#include <sge/opengl/egl/window_surface_impl.hpp>
#include <sge/opengl/egl/wayland/surface.hpp>
#include <awl/backends/wayland/window/object.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/config/external_begin.hpp>
#include <EGL/egl.h>
#include <fcppt/config/external_end.hpp>


sge::opengl::egl::wayland::surface::surface(
	EGLDisplay const _display,
	EGLConfig const _config,
	awl::backends::wayland::window::object &_window
)
:
	sge::opengl::egl::surface(),
	window_{
		_window
	},
	surface_{
		_display,
		_config,
		window_.get()
	}
{
}

sge::opengl::egl::wayland::surface::~surface()
{
}

EGLSurface
sge::opengl::egl::wayland::surface::get() const
{
	return
		surface_.get();
}
