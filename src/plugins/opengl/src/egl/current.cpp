/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2015 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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


#include <sge/opengl/backend/current.hpp>
#include <sge/opengl/backend/fun_ptr.hpp>
#include <sge/opengl/egl/current.hpp>
#include <sge/opengl/egl/swap_buffers.hpp>
#include <sge/opengl/egl/window_surface.hpp>
#include <fcppt/config/external_begin.hpp>
#include <EGL/egl.h>
#include <string>
#include <fcppt/config/external_end.hpp>


sge::opengl::egl::current::current(
	EGLDisplay const _display,
	sge::opengl::egl::window_surface const &_surface
)
:
	sge::opengl::backend::current(),
	display_(
		_display
	),
	surface_(
		_surface
	)
{
}

sge::opengl::egl::current::~current()
{
}

sge::opengl::backend::fun_ptr
sge::opengl::egl::current::load_function(
	std::string const &_name
) const
{
	return
		::eglGetProcAddress(
			_name.c_str()
		);
}

void
sge::opengl::egl::current::begin_rendering()
{
}

void
sge::opengl::egl::current::end_rendering()
{
	sge::opengl::egl::swap_buffers(
		display_,
		surface_.get()
	);
}

void
sge::opengl::egl::current::vsync(
	sge::renderer::display_mode::vsync const _vsync
)
{
}
