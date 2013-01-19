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


#include <sge/opengl/glx/context.hpp>
#include <sge/opengl/glx/make_current.hpp>
#include <sge/renderer/exception.hpp>
#include <awl/backends/x11/display.hpp>
#include <awl/backends/x11/visual/object.hpp>
#include <awl/backends/x11/window/object.hpp>
#include <fcppt/text.hpp>
#include <fcppt/config/external_begin.hpp>
#include <GL/glx.h>
#include <X11/X.h>
#include <X11/Xutil.h>
#include <fcppt/config/external_end.hpp>


sge::opengl::glx::context::context(
	awl::backends::x11::window::object &_window
)
:
	window_(
		_window
	),
	context_(
		::glXCreateContext(
			_window.display().get(),
			const_cast<
				XVisualInfo *
			>(
				&window_.visual().info()
			),
			nullptr,
			True
		)
	)
{
	if(
		context_
		==
		nullptr
	)
		throw sge::renderer::exception(
			FCPPT_TEXT("glXCreateContext() failed!")
		);
}

sge::opengl::glx::context::~context()
{
	::glXDestroyContext(
		window_.display().get(),
		context_
	);
}

void
sge::opengl::glx::context::activate()
{
	sge::opengl::glx::make_current(
		window_.display().get(),
		window_.get(),
		context_
	);
}

void
sge::opengl::glx::context::deactivate()
{
	sge::opengl::glx::make_current(
		window_.display().get(),
		None,
		nullptr
	);
}

void
sge::opengl::glx::context::begin_rendering()
{
}

void
sge::opengl::glx::context::end_rendering()
{
	if(
		!window_.destroyed()
	)
		::glXSwapBuffers(
			window_.display().get(),
			window_.get()
		);
}
