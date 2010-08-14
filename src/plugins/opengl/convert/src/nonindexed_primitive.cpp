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


#include "../nonindexed_primitive.hpp"
#include <sge/renderer/exception.hpp>
#include <fcppt/text.hpp>

GLenum
sge::opengl::convert::nonindexed_primitive(
	renderer::nonindexed_primitive_type::type const _type
)
{
	switch(_type)
	{
	case renderer::nonindexed_primitive_type::point:
		return GL_POINTS;
	case renderer::nonindexed_primitive_type::line:
		return GL_LINES;
	case renderer::nonindexed_primitive_type::line_strip:
		return GL_LINE_STRIP;
	case renderer::nonindexed_primitive_type::triangle:
		return GL_TRIANGLES;
	case renderer::nonindexed_primitive_type::triangle_strip:
		return GL_TRIANGLE_STRIP;
	case renderer::nonindexed_primitive_type::triangle_fan:
		return GL_TRIANGLE_FAN;
	}

	throw renderer::exception(
		FCPPT_TEXT("Invalid indexed_primitive_type!")
	);
}
