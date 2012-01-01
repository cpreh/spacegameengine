/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2012 Carl Philipp Reh (sefi@s-e-f-i.de)

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU Lesser General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
*/


#include <sge/opengl/error_string.hpp>
#include <fcppt/text.hpp>

fcppt::string const
sge::opengl::error_string(
	GLenum const _what
)
{
	switch(
		_what
	)
	{
	case GL_NO_ERROR:
		return FCPPT_TEXT("GL_NO_ERROR");
	case GL_INVALID_ENUM:
		return FCPPT_TEXT("GL_INVALID_ENUM");
	case GL_INVALID_VALUE:
		return FCPPT_TEXT("GL_INVALID_VALUE");
	case GL_INVALID_OPERATION:
		return FCPPT_TEXT("GL_INVALID_OPERATION");
	case GL_STACK_OVERFLOW:
		return FCPPT_TEXT("GL_STACK_OVERFLOW");
	case GL_STACK_UNDERFLOW:
		return FCPPT_TEXT("GL_STACK_UNDERFLOW");
	case GL_OUT_OF_MEMORY:
		return FCPPT_TEXT("GL_OUT_OF_MEMORY");
	case GL_TABLE_TOO_LARGE:
		return FCPPT_TEXT("GL_TABLE_TOO_LARGE");
	}

	return FCPPT_TEXT("Unknown");
}
