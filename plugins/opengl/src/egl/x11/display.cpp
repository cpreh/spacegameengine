//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/opengl/egl/display.hpp>
#include <sge/opengl/egl/get_display.hpp>
#include <sge/opengl/egl/init_fwd.hpp>
#include <sge/opengl/egl/surface.hpp>
#include <sge/opengl/egl/surface_unique_ptr.hpp>
#include <sge/opengl/egl/x11/display.hpp>
#include <sge/opengl/egl/x11/surface.hpp>
#include <sge/opengl/egl/x11/visual.hpp>
#include <sge/renderer/pixel_format/object_fwd.hpp>
#include <sge/window/object.hpp>
#include <awl/backends/x11/display.hpp>
#include <awl/backends/x11/system/object.hpp>
#include <awl/backends/x11/window/base.hpp>
#include <awl/visual/object.hpp>
#include <awl/visual/object_unique_ptr.hpp>
#include <awl/window/object.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/unique_ptr_to_base.hpp>
#include <fcppt/cast/dynamic_exn.hpp>
#include <fcppt/log/object_fwd.hpp>
#include <fcppt/config/external_begin.hpp>
#include <EGL/egl.h>
#include <fcppt/config/external_end.hpp>


sge::opengl::egl::x11::display::display(
	fcppt::log::object &_log,
	awl::backends::x11::system::object &_awl_system
)
:
	sge::opengl::egl::display(),
	log_{
		_log
	},
	x11_display_{
		_awl_system.display()
	},
	display_{
		sge::opengl::egl::get_display(
			x11_display_.get()
		)
	}
{
}

sge::opengl::egl::x11::display::~display()
{
}

EGLDisplay
sge::opengl::egl::x11::display::get() const
{
	return
		display_;
}

awl::visual::object_unique_ptr
sge::opengl::egl::x11::display::create_visual(
	sge::opengl::egl::init const &,
	sge::renderer::pixel_format::object const &_pixel_format
)
{
	return
		fcppt::unique_ptr_to_base<
			awl::visual::object
		>(
			fcppt::make_unique_ptr<
				sge::opengl::egl::x11::visual
			>(
				log_,
				x11_display_,
				display_,
				_pixel_format
			)
		);
}

sge::opengl::egl::surface_unique_ptr
sge::opengl::egl::x11::display::create_surface(
	EGLConfig const _config,
	sge::window::object &_window
)
{
	return
		fcppt::unique_ptr_to_base<
			sge::opengl::egl::surface
		>(
			fcppt::make_unique_ptr<
				sge::opengl::egl::x11::surface
			>(
				display_,
				_config,
				fcppt::cast::dynamic_exn<
					awl::backends::x11::window::base const &
				>(
					_window.awl_object()
				)
			)
		);
}
