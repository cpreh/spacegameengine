/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2014 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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


#include <sge/opengl/egl/attribute_vector.hpp>
#include <sge/opengl/egl/context_impl.hpp>
#include <sge/opengl/egl/make_current.hpp>
#include <sge/opengl/egl/no_context.hpp>
#include <sge/opengl/egl/no_surface.hpp>
#include <sge/renderer/exception.hpp>
#include <fcppt/text.hpp>
#include <fcppt/assert/error.hpp>
#include <fcppt/config/external_begin.hpp>
#include <EGL/egl.h>
#include <fcppt/config/external_end.hpp>


sge::opengl::egl::context_impl::context_impl(
	EGLDisplay const _display,
	EGLConfig const _config
)
:
	display_(
		_display
	),
	context_(
		::eglCreateContext(
			_display,
			_config,
			EGL_NO_CONTEXT,
			sge::opengl::egl::attribute_vector{
				EGL_CONTEXT_CLIENT_VERSION,
				2,
				EGL_NONE
			}.data()
		)
	)
{
	if(
		context_
		==
		sge::opengl::egl::no_context
	)
		throw
			sge::renderer::exception(
				FCPPT_TEXT("eglCreateContext failed")
			);
}

sge::opengl::egl::context_impl::~context_impl()
{
	FCPPT_ASSERT_ERROR(
		::eglDestroyContext(
			display_,
			context_
		)
		==
		EGL_TRUE
	);
}

void
sge::opengl::egl::context_impl::activate(
	EGLSurface const _surface
)
{
	sge::opengl::egl::make_current(
		display_,
		_surface,
		context_
	);
}

void
sge::opengl::egl::context_impl::deactivate()
{
	sge::opengl::egl::make_current(
		display_,
		sge::opengl::egl::no_surface,
		sge::opengl::egl::no_context
	);
}
