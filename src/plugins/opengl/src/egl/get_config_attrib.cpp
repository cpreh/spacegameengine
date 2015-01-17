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


#include <sge/opengl/egl/get_config_attrib.hpp>
#include <sge/renderer/exception.hpp>
#include <fcppt/text.hpp>
#include <fcppt/config/external_begin.hpp>
#include <EGL/egl.h>
#include <fcppt/config/external_end.hpp>


EGLint
sge::opengl::egl::get_config_attrib(
	EGLDisplay const _egl_display,
	EGLConfig const _egl_config,
	EGLint const _attrib
)
{
	EGLint result;

	if(
		::eglGetConfigAttrib(
			_egl_display,
			_egl_config,
			_attrib,
			&result
		)
		!=
		EGL_TRUE
	)
		throw
			sge::renderer::exception(
				FCPPT_TEXT("eglGetConfigAttrib failed")
			);

	return
		result;
}
