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
#include "../resolution/instance.hpp"
#include "../../glx/context.hpp"
#include <sge/renderer/viewport.hpp>
#include <sge/renderer/parameters.hpp>
#include <awl/backends/x11/visual.hpp>
#include <awl/backends/x11/window_instance.hpp>
#include <awl/backends/x11/display.hpp>
//#include <fcppt/assign/make_container.hpp>
#include <fcppt/math/dim/basic_impl.hpp>
//#include <fcppt/signal/shared_connection.hpp>
#include <fcppt/tr1/functional.hpp>
#include <fcppt/make_shared_ptr.hpp>

sge::opengl::x11::state::state(
	renderer::parameters const &_param,
	renderer::adapter_type const _adapter,
	awl::backends::x11::window_instance_ptr const _window,
	opengl::viewport_fun const &_set_viewport
)
:
	device_state(),
	set_viewport_(
		_set_viewport
	),
	screen_size_(
		_param.display_mode().size()
	),
	window_(
		_window
	),
	display_(
		window_->display()
	),
	visual_(
		window_->visual()
	),
	context_(
		fcppt::make_shared_ptr<
			glx::context
		>(
			display_,
			*fcppt::dynamic_pointer_cast<
				awl::backends::x11::visual const
			>(
				visual_
			)->info()
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
	),
	connection_manager_()
	/*
		fcppt::assign::make_container<
			fcppt::signal::connection_manager
		>(
			fcppt::signal::shared_connection(
				window_->register_callback(
					MapNotify,
					std::tr1::bind(
						&state::reset_viewport_on_map,
						this,
						std::tr1::placeholders::_1
					)
				)
			)
		)
		(
			fcppt::signal::shared_connection(
				window_->register_callback(
					ConfigureNotify,
					std::tr1::bind(
						&state::reset_viewport_on_configure,
						this,
						std::tr1::placeholders::_1
					)
				)
			)
		)
	)*/
{
}

sge::opengl::x11::state::~state()
{
}

void
sge::opengl::x11::state::swap_buffers()
{
	::glXSwapBuffers(
		display_->get(),
		window_->get()
	);
}

void
sge::opengl::x11::state::reset_viewport_on_map(
	XEvent const &
)
{
	// TODO?
#if 0
	set_viewport_(
		window_->size()
	);
#endif
}

void
sge::opengl::x11::state::reset_viewport_on_configure(
	XEvent const &_event
)
{
	XConfigureEvent const &configure_event(
		_event.xconfigure
	);

	set_viewport_(
		window::dim_type(
			configure_event.width,
			configure_event.height
		)
	);
}
