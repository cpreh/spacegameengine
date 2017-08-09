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


#include <sge/opengl/egl/surface.hpp>
#include <sge/opengl/egl/window_surface_impl.hpp>
#include <sge/opengl/egl/x11/surface.hpp>
#include <awl/backends/x11/window/base.hpp>
#include <fcppt/config/external_begin.hpp>
#include <EGL/egl.h>
#include <fcppt/config/external_end.hpp>


sge::opengl::egl::x11::surface::surface(
	EGLDisplay const _display,
	EGLConfig const _config,
	awl::backends::x11::window::base const &_surface
)
:
	sge::opengl::egl::surface(),
	surface_{
		_display,
		_config,
		_surface.get()
	}
{
}

sge::opengl::egl::x11::surface::~surface()
{
}

EGLSurface
sge::opengl::egl::x11::surface::get() const
{
	return
		surface_.get();
}
