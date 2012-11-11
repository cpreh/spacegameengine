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


#include <sge/opengl/device_state/context.hpp>
#include <sge/opengl/glx/context.hpp>
#include <sge/opengl/glx/make_current.hpp>
#include <sge/opengl/x11/context.hpp>
#include <awl/backends/x11/display.hpp>
#include <awl/backends/x11/visual/object.hpp>
#include <awl/backends/x11/window/object.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/null_ptr.hpp>
#include <fcppt/ref.hpp>
#include <fcppt/config/external_begin.hpp>
#include <GL/glx.h>
#include <fcppt/config/external_end.hpp>


sge::opengl::x11::context::context(
	awl::backends::x11::window::object &_window
)
:
	sge::opengl::device_state::context(),
	window_(
		_window
	),
	display_(
		window_.display()
	),
	glx_context_(
		fcppt::make_unique_ptr<
			sge::opengl::glx::context
		>(
			fcppt::ref(
				display_
			),
			window_.visual().info()
		)
	)
{
}

sge::opengl::x11::context::~context()
{
}

void
sge::opengl::x11::context::activate()
{
	sge::opengl::glx::make_current(
		display_.get(),
		window_.get(),
		glx_context_->get()
	);
}

void
sge::opengl::x11::context::deactivate()
{
	sge::opengl::glx::make_current(
		display_.get(),
		None,
		fcppt::null_ptr()
	);
}

void
sge::opengl::x11::context::swap_buffers()
{
	::glXSwapBuffers(
		window_.display().get(),
		window_.get()
	);
}
