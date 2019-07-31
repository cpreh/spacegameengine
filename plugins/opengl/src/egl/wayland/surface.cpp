//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <fcppt/config/external_begin.hpp>
#include <wayland-egl-core.h>
#include <fcppt/config/external_end.hpp>
#define SGE_OPENGL_EGL_WAYLAND_SURFACE_CPP_EGL_CORE_ON_TOP
#include <sge/opengl/egl/surface.hpp>
#include <sge/opengl/egl/window_surface_impl.hpp>
#include <sge/opengl/egl/wayland/surface.hpp>
#include <sge/window/object_fwd.hpp>
#include <awl/backends/wayland/window/object.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/config/external_begin.hpp>
#include <EGL/egl.h>
#include <fcppt/config/external_end.hpp>


sge::opengl::egl::wayland::surface::surface(
	EGLDisplay const _display,
	EGLConfig const _config,
	sge::window::object &_window
)
:
	sge::opengl::egl::surface(),
	window_{
		_window
	},
	surface_{
		_display,
		_config,
		window_.get()
	}
{
}

sge::opengl::egl::wayland::surface::~surface()
{
}

EGLSurface
sge::opengl::egl::wayland::surface::get() const
{
	return
		surface_.get();
}
