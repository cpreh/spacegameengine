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


#include "../create_device_state.hpp"
#include <sge/opengl/config.hpp>
#include <fcppt/config.hpp>
#ifdef SGE_OPENGL_HAVE_X11
#include "../x11/state.hpp"
#include <awl/backends/x11/window_instance.hpp>
#elif FCPPT_WINDOWS_PLATFORM
#include <awl/backends/windows/window_instance.hpp>
#else
#error "Implement me!"
#endif
#include <sge/window/instance.hpp>
#include <fcppt/polymorphic_pointer_cast.hpp>
#include <fcppt/make_unique_ptr.hpp>

sge::opengl::device_state_ptr
sge::opengl::create_device_state(
	renderer::parameters const &_parameters,
	renderer::adapter_type const _adapter,
	window::instance_ptr const _window
)
{
#ifdef SGE_OPENGL_HAVE_X11
	return
		opengl::device_state_ptr(
			fcppt::make_unique_ptr<
				x11::state
			>(
				_parameters,
				_adapter,
				fcppt::polymorphic_pointer_cast<
					awl::backends::x11::window_instance
				>(
					_window->awl_instance()
				)
			)
		);
#elif FCPPT_WINDOWS_PLATFORM
	return
		fcppt::make_unique_ptr<
			windows::state
		>(
			// FIXME!
		);
#else
#error "Implement me!"
#endif
}
