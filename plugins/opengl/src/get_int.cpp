//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/opengl/common.hpp>
#include <sge/opengl/get_int.hpp>
#include <sge/opengl/get_ints.hpp>


GLint
sge::opengl::get_int(
	GLenum const _what
)
{
	GLint ret;

	sge::opengl::get_ints(
		_what,
		&ret
	);

	return
		ret;
}
