/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2015 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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
#include <sge/opengl/egl/init_fwd.hpp>
#include <sge/opengl/egl/visual/create.hpp>
#include <awl/system/object_fwd.hpp>
#include <awl/visual/object.hpp>
#include <awl/visual/object_unique_ptr.hpp>
#include <fcppt/config/external_begin.hpp>
#include <EGL/egl.h>
#include <fcppt/config/external_end.hpp>
#if defined(SGE_OPENGL_HAVE_X11)
#include <sge/opengl/egl/x11/visual.hpp>
#include <awl/backends/x11/system/object.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/unique_ptr_to_base.hpp>
#include <fcppt/cast/static_downcast.hpp>
#else
#error "Implement me!"
#endif


awl::visual::object_unique_ptr
sge::opengl::egl::visual::create(
	sge::opengl::egl::init const &,
	awl::system::object &_awl_system,
	EGLDisplay const _egl_display,
	sge::renderer::pixel_format::object const &_pixel_format
)
{
#if defined(SGE_OPENGL_HAVE_X11)
	return
		fcppt::unique_ptr_to_base<
			awl::visual::object
		>(
			fcppt::make_unique_ptr<
				sge::opengl::egl::x11::visual
			>(
				fcppt::cast::static_downcast<
					awl::backends::x11::system::object &
				>(
					_awl_system
				).display(),
				_egl_display,
				_pixel_format
			)
		);
#else
#error "Implement me!"
#endif
}
