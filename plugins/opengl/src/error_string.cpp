//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/opengl/common.hpp>
#include <sge/opengl/error_string.hpp>
#include <fcppt/string.hpp>
#include <fcppt/text.hpp>


fcppt::string
sge::opengl::error_string(
	GLenum const _what
)
{
	switch(
		_what
	)
	{
	case GL_NO_ERROR:
		return
			FCPPT_TEXT("GL_NO_ERROR");
	case GL_INVALID_ENUM:
		return
			FCPPT_TEXT("GL_INVALID_ENUM");
	case GL_INVALID_VALUE:
		return
			FCPPT_TEXT("GL_INVALID_VALUE");
	case GL_INVALID_OPERATION:
		return
			FCPPT_TEXT("GL_INVALID_OPERATION");
	case GL_STACK_OVERFLOW:
		return
			FCPPT_TEXT("GL_STACK_OVERFLOW");
	case GL_STACK_UNDERFLOW:
		return
			FCPPT_TEXT("GL_STACK_UNDERFLOW");
	case GL_OUT_OF_MEMORY:
		return
			FCPPT_TEXT("GL_OUT_OF_MEMORY");
	case GL_TABLE_TOO_LARGE:
		return
			FCPPT_TEXT("GL_TABLE_TOO_LARGE");
	default:
		return
			FCPPT_TEXT("Unknown");
	}
}
