/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2016 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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
#include <sge/opengl/platform/create_system.hpp>
#include <sge/opengl/platform/system.hpp>
#include <sge/opengl/platform/system_unique_ptr.hpp>
#include <awl/system/object.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/unique_ptr_to_base.hpp>
#include <fcppt/config/platform.hpp>
#if defined(SGE_OPENGL_HAVE_X11)
#include <sge/opengl/x11/system.hpp>
#include <awl/backends/x11/system/object.hpp>
#include <fcppt/cast/static_downcast.hpp>
#elif defined(FCPPT_CONFIG_WINDOWS_PLATFORM)
#include <sge/opengl/windows/system.hpp>
#else
#error "Implement me!"
#endif


sge::opengl::platform::system_unique_ptr
sge::opengl::platform::create_system(
	awl::system::object &_awl_system
)
{
	return
		fcppt::unique_ptr_to_base<
			sge::opengl::platform::system
		>(
#if defined(SGE_OPENGL_HAVE_X11)
			fcppt::make_unique_ptr<
				sge::opengl::x11::system
			>(
				fcppt::cast::static_downcast<
					awl::backends::x11::system::object &
				>(
					_awl_system
				)
			)
#elif defined(FCPPT_CONFIG_WINDOWS_PLATFORM)
			fcppt::make_unique_ptr<
				sge::opengl::windows::system
			>()
#else
#error "Implement me!"
#endif
		);
}
