//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/opengl/egl/surface.hpp>
#include <sge/opengl/egl/window_surface_impl.hpp>
#include <sge/opengl/egl/x11/surface.hpp>
#include <awl/backends/x11/window/base.hpp>
#include <awl/backends/x11/window/const_base_ref.hpp>
#include <fcppt/config/external_begin.hpp>
#include <EGL/egl.h>
#include <fcppt/config/external_end.hpp>


sge::opengl::egl::x11::surface::surface(
	EGLDisplay const _display, // NOLINT(misc-misplaced-const)
	EGLConfig const _config, // NOLINT(misc-misplaced-const)
	awl::backends::x11::window::const_base_ref const _surface
)
:
	sge::opengl::egl::surface(),
	surface_{
		_display,
		_config,
		_surface.get().get()
	}
{
}

sge::opengl::egl::x11::surface::~surface()
= default;

EGLSurface
sge::opengl::egl::x11::surface::get() const
{
	return
		surface_.get();
}
