//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_OPENGL_CONVERT_TO_GL_ENUM_HPP_INCLUDED
#define SGE_OPENGL_CONVERT_TO_GL_ENUM_HPP_INCLUDED

#include <sge/opengl/common.hpp>
#include <fcppt/cast/to_unsigned.hpp>


namespace sge::opengl::convert
{

template<
	int Enum
>
inline
GLenum
to_gl_enum()
{
	return
		fcppt::cast::to_unsigned(
			Enum
		);
}

}

#endif
