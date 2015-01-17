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


#include <sge/opengl/egl/no_surface.hpp>
#include <sge/opengl/egl/window_surface.hpp>
#include <sge/renderer/exception.hpp>
#include <fcppt/text.hpp>
#include <fcppt/assert/error.hpp>
#include <fcppt/config/external_begin.hpp>
#include <EGL/egl.h>
#include <fcppt/config/external_end.hpp>


sge::opengl::egl::window_surface::window_surface(
	EGLDisplay const _display,
	EGLConfig const _config,
	EGLNativeWindowType const _window
)
:
	display_(
		_display
	),
	surface_(
		::eglCreateWindowSurface(
			_display,
			_config,
			_window,
			nullptr // TODO: What do we need here?
		)
	)
{
	if(
		surface_
		==
		sge::opengl::egl::no_surface
	)
		throw
			sge::renderer::exception(
				FCPPT_TEXT("eglCreateWindowSurface failed")
			);
}

sge::opengl::egl::window_surface::~window_surface()
{
	FCPPT_ASSERT_ERROR(
		::eglDestroySurface(
			display_,
			surface_
		)
		==
		EGL_TRUE
	);
}

EGLSurface
sge::opengl::egl::window_surface::get() const
{
	return
		surface_;
}
