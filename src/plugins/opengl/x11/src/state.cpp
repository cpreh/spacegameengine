/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2011 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#include <GL/glx.h>
#include "../state.hpp"
#include "../vsync.hpp"
#include "../resolution/create.hpp"
#include "../resolution/instance.hpp"
#include "../../glx/context.hpp"
#include <sge/renderer/parameters.hpp>
#include <awl/backends/x11/visual.hpp>
#include <awl/backends/x11/window/instance.hpp>
#include <awl/backends/x11/display.hpp>
#include <fcppt/math/dim/basic_impl.hpp>
#include <fcppt/make_shared_ptr.hpp>
#include <fcppt/ref.hpp>

sge::opengl::x11::state::state(
	opengl::context::object &_context,
	renderer::parameters const &_param,
	renderer::adapter const _adapter,
	awl::backends::x11::window::instance &_window
)
:
	device_state(),
	window_(
		_window
	),
	display_(
		window_.display()
	),
	context_(
		fcppt::make_shared_ptr<
			glx::context
		>(
			fcppt::ref(
				display_
			),
			*window_.visual().info()
		)
	),
	current_(
		display_,
		window_,
		context_
	),
	resolution_(
		x11::resolution::create(
			window_,
			_param,
			_adapter
		)
	)
{
	if(
		_param.vsync()
		== sge::renderer::vsync::on
	)
		x11::vsync(
			_context
		);
}

sge::opengl::x11::state::~state()
{
}

void
sge::opengl::x11::state::swap_buffers()
{
	::glXSwapBuffers(
		display_.get(),
		window_.get()
	);
}
