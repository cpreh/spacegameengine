//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/opengl/glx/make_current.hpp>
#include <sge/renderer/exception.hpp>
#include <fcppt/text.hpp>
#include <fcppt/config/external_begin.hpp>
#include <GL/glx.h>
#include <X11/Xlib.h>
#include <fcppt/config/external_end.hpp>


void
sge::opengl::glx::make_current(
	Display *const _display,
	Window const _window,
	GLXContext const _context
)
{
	if(
		::glXMakeCurrent(
			_display,
			_window,
			_context
		)
		==
		False
	)
		throw sge::renderer::exception(
			FCPPT_TEXT("glXMakeCurrent() failed!")
		);
}

