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


#include <sge/opengl/device_state/object.hpp>
#include <sge/opengl/glx/context.hpp>
#include <sge/opengl/x11/state.hpp>
#include <sge/opengl/x11/vsync.hpp>
#include <sge/opengl/x11/resolution/create.hpp>
#include <sge/opengl/x11/resolution/object.hpp>
#include <sge/renderer/parameters/object.hpp>
#include <sge/renderer/parameters/vsync.hpp>
#include <awl/backends/x11/display.hpp>
#include <awl/backends/x11/visual/object.hpp>
#include <awl/backends/x11/window/object.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/ref.hpp>
#include <fcppt/math/dim/object_impl.hpp>
#include <fcppt/config/external_begin.hpp>
#include <GL/glx.h>
#include <fcppt/config/external_end.hpp>


sge::opengl::x11::state::state(
	sge::opengl::context::system::object &_system_context,
	sge::renderer::parameters::object const &_parameters,
	awl::backends::x11::window::object &_window
)
:
	sge::opengl::device_state::object(),
	window_(
		_window
	),
	context_(
		_window
	),
	scoped_current_(
		context_
	),
	resolution_(
		sge::opengl::x11::resolution::create(
			window_,
			_parameters.display_mode()
		)
	)
{
	if(
		_parameters.vsync()
		==
		sge::renderer::parameters::vsync::on
	)
		sge::opengl::x11::vsync(
			window_.display(),
			_system_context
		);
}

void
sge::opengl::x11::state::begin_rendering()
{
}

sge::opengl::x11::state::~state()
{
}

void
sge::opengl::x11::state::swap_buffers()
{
	if(
		!window_.destroyed()
	)
		::glXSwapBuffers(
			window_.display().get(),
			window_.get()
		);
}
