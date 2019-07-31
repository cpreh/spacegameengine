//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <fcppt/config/external_begin.hpp>
#include <wayland-egl-core.h>
#include <fcppt/config/external_end.hpp>
#define SGE_OPENGL_EGL_WAYLAND_DISPLAY_CPP_EGL_CORE_ON_TOP
#include <sge/opengl/egl/display.hpp>
#include <sge/opengl/egl/get_display.hpp>
#include <sge/opengl/egl/init_fwd.hpp>
#include <sge/opengl/egl/surface.hpp>
#include <sge/opengl/egl/surface_unique_ptr.hpp>
#include <sge/opengl/egl/wayland/display.hpp>
#include <sge/opengl/egl/wayland/surface.hpp>
#include <sge/opengl/egl/wayland/visual.hpp>
#include <sge/renderer/pixel_format/object_fwd.hpp>
#include <sge/window/object_fwd.hpp>
#include <awl/backends/wayland/display.hpp>
#include <awl/backends/wayland/system/object.hpp>
#include <awl/backends/wayland/window/object.hpp>
#include <awl/visual/object.hpp>
#include <awl/visual/object_unique_ptr.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/unique_ptr_to_base.hpp>
#include <fcppt/log/object_fwd.hpp>
#include <fcppt/config/external_begin.hpp>
#include <EGL/egl.h>
#include <fcppt/config/external_end.hpp>


sge::opengl::egl::wayland::display::display(
	fcppt::log::object &_log,
	awl::backends::wayland::system::object &_system
)
:
	sge::opengl::egl::display(),
	log_{
		_log
	},
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
				log_,
				display_,
				_pixel_format
			)
		);
}

sge::opengl::egl::surface_unique_ptr
sge::opengl::egl::wayland::display::create_surface(
	EGLConfig const _config,
	sge::window::object &_window
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
				_window
			)
		);
}
