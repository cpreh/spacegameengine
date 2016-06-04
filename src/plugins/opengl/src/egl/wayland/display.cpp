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


#include <fcppt/config/external_begin.hpp>
#include <wayland-egl-core.h>
#include <fcppt/config/external_end.hpp>
#include <sge/opengl/egl/display.hpp>
#include <sge/opengl/egl/get_display.hpp>
#include <sge/opengl/egl/init_fwd.hpp>
#include <sge/opengl/egl/surface.hpp>
#include <sge/opengl/egl/surface_unique_ptr.hpp>
#include <sge/opengl/egl/wayland/display.hpp>
#include <sge/opengl/egl/wayland/surface.hpp>
#include <sge/opengl/egl/wayland/visual.hpp>
#include <sge/renderer/pixel_format/object_fwd.hpp>
#include <awl/backends/wayland/display.hpp>
#include <awl/backends/wayland/system/object.hpp>
#include <awl/backends/wayland/window/object.hpp>
#include <awl/visual/object.hpp>
#include <awl/visual/object_unique_ptr.hpp>
#include <awl/window/object.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/unique_ptr_to_base.hpp>
#include <fcppt/cast/dynamic_exn.hpp>
#include <fcppt/config/external_begin.hpp>
#include <EGL/egl.h>
#include <fcppt/config/external_end.hpp>


sge::opengl::egl::wayland::display::display(
	awl::backends::wayland::system::object &_system
)
:
	sge::opengl::egl::display(),
	display_{
		sge::opengl::egl::get_display(
			_system.display().get()
		)
	}
{
}

sge::opengl::egl::wayland::display::~display()
{
}

EGLDisplay
sge::opengl::egl::wayland::display::get() const
{
	return
		display_;
}

awl::visual::object_unique_ptr
sge::opengl::egl::wayland::display::create_visual(
	sge::opengl::egl::init const &,
	sge::renderer::pixel_format::object const &_pixel_format
)
{
	return
		fcppt::unique_ptr_to_base<
			awl::visual::object
		>(
			fcppt::make_unique_ptr<
				sge::opengl::egl::wayland::visual
			>(
				display_,
				_pixel_format
			)
		);
}

sge::opengl::egl::surface_unique_ptr
sge::opengl::egl::wayland::display::create_surface(
	EGLConfig const _config,
	awl::window::object &_window
)
{
	return
		fcppt::unique_ptr_to_base<
			sge::opengl::egl::surface
		>(
			fcppt::make_unique_ptr<
				sge::opengl::egl::wayland::surface
			>(
				display_,
				_config,
				fcppt::cast::dynamic_exn<
					awl::backends::wayland::window::object &
				>(
					_window
				)
			)
		);
}
