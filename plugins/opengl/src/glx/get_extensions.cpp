//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/opengl/parse_extensions.hpp>
#include <sge/opengl/glx/extension.hpp>
#include <sge/opengl/glx/extension_set.hpp>
#include <sge/opengl/glx/get_extensions.hpp>
#include <awl/backends/x11/default_screen.hpp>
#include <awl/backends/x11/display.hpp>
#include <fcppt/config/external_begin.hpp>
#include <GL/glx.h>
#include <fcppt/config/external_end.hpp>


sge::opengl::glx::extension_set
sge::opengl::glx::get_extensions(
	awl::backends::x11::display const &_display
)
{
#if defined(GLX_VERSION_1_1)
	const char *const result(
		::glXQueryExtensionsString(
			_display.get(),
			awl::backends::x11::default_screen(
				_display
			).get()
		)
	);

	return
		result
		==
		nullptr
		?
			sge::opengl::glx::extension_set()
		:
			sge::opengl::parse_extensions<
				sge::opengl::glx::extension
			>(
				result
			)
		;
#else
	return
		sge::opengl::glx::extension_set();
#endif
}
