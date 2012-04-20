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
#include <sge/opengl/create_visual.hpp>
#include <sge/renderer/parameters_fwd.hpp>
#include <awl/system/object_fwd.hpp>
#include <awl/visual/object.hpp>
#include <awl/visual/object_unique_ptr.hpp>
#include <fcppt/config/platform.hpp>
#if defined(SGE_OPENGL_HAVE_X11)
#include <sge/opengl/glx/visual/create.hpp>
#include <awl/backends/x11/system/object.hpp>
#elif defined(FCPPT_CONFIG_WINDOWS_PLATFORM)
#include <sge/opengl/windows/visual/create.hpp>
#else
#error "Implement me!"
#endif


awl::visual::object_unique_ptr
sge::opengl::create_visual(
#if defined(SGE_OPENGL_HAVE_X11)
	awl::system::object &_awl_system,
#elif defined(FCPPT_CONFIG_WINDOWS_PLATFORM)
	awl::system::object &,
#endif
	sge::renderer::parameters const &_parameters
)
{
#if defined(SGE_OPENGL_HAVE_X11)
	return
		sge::opengl::glx::visual::create(
			dynamic_cast<
				awl::backends::x11::system::object &
			>(
				_awl_system
			),
			_parameters
		);
#elif defined(FCPPT_CONFIG_WINDOWS_PLATFORM)
	return
		sge::opengl::windows::visual::create(
			_parameters
		);
#else
#error "Implement me!"
#endif
}
