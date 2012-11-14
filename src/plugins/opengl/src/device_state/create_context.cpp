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


#include <sge/opengl/config.hpp>
#include <sge/opengl/context/system/object_fwd.hpp>
#include <sge/opengl/device_state/context_unique_ptr.hpp>
#include <sge/opengl/device_state/create_context.hpp>
#include <awl/window/object_fwd.hpp>
#include <fcppt/config/platform.hpp>
#if defined(SGE_OPENGL_HAVE_X11)
#include <sge/opengl/glx/context.hpp>
#include <awl/backends/x11/window/object.hpp>
#elif defined(FCPPT_CONFIG_WINDOWS_PLATFORM)
#include <sge/opengl/windows/context.hpp>
#include <awl/backends/windows/window/object.hpp>
#else
#error "Implement me!"
#endif
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/ref.hpp>


sge::opengl::device_state::context_unique_ptr
sge::opengl::device_state::create_context(
	sge::opengl::context::system::object &_system_context,
	awl::window::object &_window
)
{
#if defined(SGE_OPENGL_HAVE_X11)
	return
		sge::opengl::device_state::context_unique_ptr(
			fcppt::make_unique_ptr<
				sge::opengl::glx::context
			>(
				fcppt::ref(
					_system_context
				),
				fcppt::ref(
					dynamic_cast<
						awl::backends::x11::window::object &
					>(
						_window
					)
				)
			)
		);
#elif defined(FCPPT_CONFIG_WINDOWS_PLATFORM)
	return
		sge::opengl::device_state::context_unique_ptr(
			fcppt::make_unique_ptr<
				sge::opengl::windows::context
			>(
				fcppt::ref(
					dynamic_cast<
						awl::backends::windows::window::object &
					>(
						_window
					)
				)
			)
		);
#else
#error "Implement me!"
#endif
}
