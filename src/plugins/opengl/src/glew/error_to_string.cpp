/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2013 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#include <sge/opengl/common.hpp>
#include <sge/opengl/glew/error_to_string.hpp>
#include <fcppt/string.hpp>
#include <fcppt/text.hpp>


fcppt::string
sge::opengl::glew::error_to_string(
	GLenum const _what
)
{
	switch(
		_what
	)
	{
	case GLEW_ERROR_NO_GL_VERSION:
		return
			FCPPT_TEXT("Missing GL version");
	case GLEW_ERROR_GL_VERSION_10_ONLY:
		return
			FCPPT_TEXT("Only GL version 1.0");
	case GLEW_ERROR_GLX_VERSION_11_ONLY:
		return
			FCPPT_TEXT("Only GLX version 1.1");
	}

	return
		FCPPT_TEXT("Unknown error");
}
