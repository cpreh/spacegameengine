//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/opengl/egl/init.hpp>
#include <sge/opengl/egl/initialize.hpp>
#include <sge/opengl/egl/version.hpp>
#include <fcppt/assert/error.hpp>
#include <fcppt/config/external_begin.hpp>
#include <EGL/egl.h>
#include <fcppt/config/external_end.hpp>


sge::opengl::egl::init::init(
	EGLDisplay const _display
)
:
	display_(
		_display
	),
	version_(
		sge::opengl::egl::initialize(
			_display
		)
	)
{
}

sge::opengl::egl::init::~init()
{
	FCPPT_ASSERT_ERROR(
		::eglTerminate(
			display_
		)
		==
		EGL_TRUE
	);
}

sge::opengl::egl::version const
sge::opengl::egl::init::version() const
{
	return
		version_;
}
