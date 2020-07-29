//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/opengl/fbo/id.hpp>
#include <sge/opengl/fbo/no_buffer.hpp>


sge::opengl::fbo::id
sge::opengl::fbo::no_buffer()
{
	return
		sge::opengl::fbo::id(
			0U
		);
}
