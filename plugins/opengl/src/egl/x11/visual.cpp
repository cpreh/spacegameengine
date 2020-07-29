//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/opengl/egl/visual/base.hpp>
#include <sge/opengl/egl/x11/create_visual_info.hpp>
#include <sge/opengl/egl/x11/visual.hpp>
#include <sge/renderer/pixel_format/object_fwd.hpp>
#include <awl/backends/x11/const_display_ref.hpp>
#include <awl/backends/x11/visual/wrapped.hpp>
#include <fcppt/log/object_fwd.hpp>
#include <fcppt/config/external_begin.hpp>
#include <EGL/egl.h>
#include <fcppt/config/external_end.hpp>


sge::opengl::egl::x11::visual::visual(
	fcppt::log::object &_log,
	awl::backends::x11::const_display_ref const _display,
	EGLDisplay const _egl_display, // NOLINT(misc-misplaced-const)
	sge::renderer::pixel_format::object const &_pixel_format
)
:
	sge::opengl::egl::visual::base(
		_log,
		_egl_display,
		_pixel_format
	),
	awl::backends::x11::visual::wrapped(
		sge::opengl::egl::x11::create_visual_info(
			_display,
			_egl_display,
			this->config()
		)
	)
{
}

sge::opengl::egl::x11::visual::~visual()
= default;
