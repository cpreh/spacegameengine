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


#include <sge/opengl/config.hpp>
#include <sge/opengl/device_state/create_system.hpp>
#include <sge/opengl/device_state/system.hpp>
#include <sge/opengl/device_state/system_unique_ptr.hpp>
#include <sge/opengl/context/system/object_fwd.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/config/platform.hpp>
#if defined(SGE_OPENGL_HAVE_EGL)
#include <sge/opengl/egl/system.hpp>
#elif defined(SGE_OPENGL_HAVE_X11)
#include <sge/opengl/glx/system.hpp>
#elif defined(FCPPT_CONFIG_WINDOWS_PLATFORM)
#include <sge/opengl/wgl/system.hpp>
#else
#error "Implement me!"
#endif


sge::opengl::device_state::system_unique_ptr
sge::opengl::device_state::create_system(
	sge::opengl::context::system::object &_system_context
)
{
#if defined(SGE_OPENGL_HAVE_EGL)
	return
		sge::opengl::device_state::system_unique_ptr(
			fcppt::make_unique_ptr<
				sge::opengl::egl::system
			>()
		);
#elif defined(SGE_OPENGL_HAVE_X11)
	return
		sge::opengl::device_state::system_unique_ptr(
			fcppt::make_unique_ptr<
				sge::opengl::glx::system
			>(
				_system_context
			)
		);
#elif defined(FCPPT_CONFIG_WINDOWS_PLATFORM)
	return
		sge::opengl::device_state::system_unique_ptr(
			fcppt::make_unique_ptr<
				sge::opengl::wgl::system
			>(
				_system_context
			)
		);
#else
#error "Implement me!"
#endif
}
