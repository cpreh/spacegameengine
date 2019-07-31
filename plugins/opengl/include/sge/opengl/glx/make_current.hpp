//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_OPENGL_GLX_MAKE_CURRENT_HPP_INCLUDED
#define SGE_OPENGL_GLX_MAKE_CURRENT_HPP_INCLUDED

#include <fcppt/config/external_begin.hpp>
#include <GL/glx.h>
#include <X11/Xlib.h>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace opengl
{
namespace glx
{

void
make_current(
	Display *,
	Window,
	GLXContext
);

}
}
}

#endif
