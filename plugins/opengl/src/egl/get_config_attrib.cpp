//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/opengl/egl/get_config_attrib.hpp>
#include <sge/renderer/exception.hpp>
#include <fcppt/text.hpp>
#include <fcppt/config/external_begin.hpp>
#include <EGL/egl.h>
#include <fcppt/config/external_end.hpp>


EGLint
sge::opengl::egl::get_config_attrib(
	EGLDisplay const _egl_display, // NOLINT(misc-misplaced-const)
	EGLConfig const _egl_config, // NOLINT(misc-misplaced-const)
	EGLint const _attrib
)
{
	EGLint result{};

	if(
		::eglGetConfigAttrib(
			_egl_display,
			_egl_config,
			_attrib,
			&result
		)
		!=
		EGL_TRUE
	)
	{
		throw
			sge::renderer::exception(
				FCPPT_TEXT("eglGetConfigAttrib failed")
			);
	}

	return
		result;
}
