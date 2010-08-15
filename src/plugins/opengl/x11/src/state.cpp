/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2010 Carl Philipp Reh (sefi@s-e-f-i.de)

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
#include "../resolution/create.hpp"
#include "../../glx/visual.hpp"
#include <sge/x11/window.hpp>
#include <sge/x11/display.hpp>
#include <sge/x11/visual.hpp>
#include <sge/renderer/viewport.hpp>
#include <sge/renderer/parameters.hpp>
#include <fcppt/math/dim/basic_impl.hpp>
#include <fcppt/tr1/functional.hpp>
#include <fcppt/make_shared_ptr.hpp>

sge::opengl::x11::state::state(
	renderer::parameters const &param,
	renderer::adapter_type const adapter,
	window::instance_ptr const wnd_,
	view_port_fun const &set_viewport
)
:
	set_viewport(
		set_viewport
	),
	screen_size_(
		param.display_mode().size()
	),
	wnd(
		fcppt::polymorphic_pointer_cast<
			sge::x11::window
		>(
			wnd_
		)
	),
	display(
		wnd->display()
	),
	visual(
		wnd->visual()
	),
	context(
		fcppt::make_shared_ptr<
			glx::context
		>(
			display,
			fcppt::dynamic_pointer_cast<
				glx::visual const
			>(
				visual
			)->info()
		)
	),
	current(
		display,
		*wnd,
		context
	),
	resolution_(
		resolution::create(
			wnd,
			param,
			adapter
		)
	)
{
	con_manager.connect(
		wnd->register_callback(
			MapNotify,
			std::tr1::bind(
				&state::reset_viewport_on_map,
				this,
				std::tr1::placeholders::_1
			)
		)
	);

	con_manager.connect(
		wnd->register_callback(
			ConfigureNotify,
			std::tr1::bind(
				&state::reset_viewport_on_configure,
				this,
				std::tr1::placeholders::_1
			)
		)
	);

	if(resolution_)
		wnd->map_raised();
	else
		wnd->map();

	display->sync();
}

void
sge::opengl::x11::state::swap_buffers()
{
	glXSwapBuffers(
		display->get(),
		wnd->get()
	);
}

void
sge::opengl::x11::state::reset_viewport_on_map(
	XEvent const &
)
{
	set_viewport(
		wnd->size()
	);
}

void
sge::opengl::x11::state::reset_viewport_on_configure(
	XEvent const &e
)
{
	XConfigureEvent const &r(
		e.xconfigure
	);

	set_viewport(
		window::dim_type(
			r.width,
			r.height
		)
	);
}
