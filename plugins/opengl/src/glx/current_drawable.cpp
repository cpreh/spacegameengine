//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/opengl/glx/current_drawable.hpp>
#include <sge/renderer/exception.hpp>
#include <fcppt/text.hpp>
#include <fcppt/config/external_begin.hpp>
#include <GL/glx.h>
#include <fcppt/config/external_end.hpp>


GLXDrawable
sge::opengl::glx::current_drawable()
{
	GLXDrawable const ret(
		::glXGetCurrentDrawable()
	);

	if(
		ret
		==
		None
	)
	{
		throw
			sge::renderer::exception(
				FCPPT_TEXT("glXGetCurrentDrawable(): No drawable set!")
			);
	}

	return
		ret;
}
