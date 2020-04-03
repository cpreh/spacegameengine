//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/opengl/egl/get_config_attrib.hpp>
#include <sge/opengl/egl/x11/create_visual_info.hpp>
#include <awl/backends/x11/display_fwd.hpp>
#include <awl/backends/x11/visual/get_info.hpp>
#include <awl/backends/x11/visual/info_unique_ptr.hpp>
#include <awl/backends/x11/visual/mask.hpp>
#include <fcppt/cast/to_unsigned.hpp>
#include <fcppt/config/external_begin.hpp>
#include <EGL/egl.h>
#include <fcppt/config/external_end.hpp>


awl::backends::x11::visual::info_unique_ptr
sge::opengl::egl::x11::create_visual_info(
	awl::backends::x11::display const &_display,
	EGLDisplay const _egl_display,
	EGLConfig const _egl_config
)
{
	XVisualInfo info;

	info.visualid =
		fcppt::cast::to_unsigned(
			sge::opengl::egl::get_config_attrib(
				_egl_display,
				_egl_config,
				EGL_NATIVE_VISUAL_ID
			)
		);

	return
		awl::backends::x11::visual::get_info(
			_display,
			awl::backends::x11::visual::mask{
				VisualIDMask
			},
			info
		);
}
