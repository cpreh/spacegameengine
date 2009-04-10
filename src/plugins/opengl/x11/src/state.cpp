/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2007  Carl Philipp Reh (sefi@s-e-f-i.de)

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
#include "../../error.hpp"
#include <sge/x11/window.hpp>
#include <sge/x11/display.hpp>
#include <sge/renderer/viewport.hpp>
#include <sge/renderer/parameters.hpp>
#include <sge/math/dim/basic_impl.hpp>
#include <sge/make_shared_ptr.hpp>
#include <boost/bind.hpp>

sge::ogl::x11::state::state(
	renderer::parameters const &param,
	renderer::adapter_type const adapter,
	window::instance_ptr const wnd_,
	view_port_fun const &set_viewport)
:
	set_viewport(
		set_viewport),
	screen_size_(
		param.mode().size()),	
	wnd(
		polymorphic_pointer_cast<sge::x11::window>(
			wnd_)),
	display(
		wnd->display()),
	visual(
		wnd->visual()),
	context(
		make_shared_ptr<glx::context>(
			display,
			dynamic_pointer_cast<glx::visual const>(
				visual)
					->info())),
	current(
		display,
		*wnd,
		context),
	resolution_(
		resolution::create(
			wnd,
			param,
			adapter))
{
 	con_manager.connect(
		wnd->register_callback(
			MapNotify,
			boost::bind(
				&state::reset_viewport_on_map,
				this,
				_1)));

	con_manager.connect(
		wnd->register_callback(
			ConfigureNotify,
			boost::bind(
				&state::reset_viewport_on_configure,
				this,
				_1)));

	if(resolution_)
		wnd->map_raised();
	else
		wnd->map();

	display->sync();
}

void sge::ogl::x11::state::swap_buffers()
{
	SGE_OPENGL_SENTRY

	glXSwapBuffers(
		display->get(),
		wnd->get());
}

void sge::ogl::x11::state::reset_viewport_on_map(
	XEvent const &)
{
	set_viewport(
		wnd->size()
	);
}

void sge::ogl::x11::state::reset_viewport_on_configure(
	XEvent const &e)
{
	XConfigureEvent const &r(
		e.xconfigure);

	set_viewport(
		window::dim_type(
			r.width,
			r.height
		)
	);
}
