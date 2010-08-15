/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2010 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#include "../depth_func.hpp"
#include <sge/exception.hpp>
#include <fcppt/text.hpp>

GLenum
sge::opengl::convert::depth_func(
	renderer::state::depth_func::type const f
)
{
	switch(f) {
	case renderer::state::depth_func::never:
		return GL_NEVER;
	case renderer::state::depth_func::less:
		return GL_LESS;
	case renderer::state::depth_func::equal:
		return GL_EQUAL;
	case renderer::state::depth_func::less_equal:
		return GL_LEQUAL;
	case renderer::state::depth_func::greater:
		return GL_GREATER;
	case renderer::state::depth_func::not_equal:
		return GL_NOTEQUAL;
	case renderer::state::depth_func::greater_equal:
		return GL_GEQUAL;
	case renderer::state::depth_func::always:
		return GL_ALWAYS;
	case renderer::state::depth_func::off:
		break;
	}

	throw exception(
		FCPPT_TEXT("Invalid depth_func!")
	);
}
