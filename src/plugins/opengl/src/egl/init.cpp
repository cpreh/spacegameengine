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


#include <sge/opengl/egl/init.hpp>
#include <sge/opengl/egl/initialize.hpp>
#include <sge/opengl/egl/version.hpp>
#include <fcppt/assert/error.hpp>
#include <fcppt/config/external_begin.hpp>
#include <EGL/egl.h>
#include <fcppt/config/external_end.hpp>


sge::opengl::egl::init::init(
	EGLDisplay const _display
)
:
	display_(
		_display
	),
	version_(
		sge::opengl::egl::initialize(
			_display
		)
	)
{
}

sge::opengl::egl::init::~init()
{
	FCPPT_ASSERT_ERROR(
		::eglTerminate(
			display_
		)
		==
		EGL_TRUE
	);
}

sge::opengl::egl::version const
sge::opengl::egl::init::version() const
{
	return
		version_;
}
