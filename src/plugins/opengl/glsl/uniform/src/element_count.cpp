/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2011 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#include "../element_count.hpp"
#include <sge/renderer/glsl/exception.hpp>
#include <fcppt/text.hpp>

sge::opengl::glsl::uniform::size_type
sge::opengl::glsl::uniform::element_count(
	sge::opengl::glsl::uniform::element_type::type const _type
)
{
	namespace et = sge::opengl::glsl::uniform::element_type;

	switch(_type)
	{
	case et::int1:
		return 1;
	case et::int2:
		return 2;
	case et::int3:
		return 3;
	case et::int4:
		return 4;
	case et::float1:
		return 1;
	case et::float2:
		return 2;
	case et::float3:
		return 3;
	case et::float4:
		return 4;
	case et::matrix2x2:
		return 4;
	case et::matrix3x3:
		return 9;
	case et::matrix4x4:
		return 16;
	case et::matrix2x3:
	case et::matrix3x2:
		return 6;
	case et::matrix2x4:
	case et::matrix4x2:
		return 8;
	case et::matrix3x4:
	case et::matrix4x3:
		return 12;
	case et::nothing:
		break;
	}

	throw sge::renderer::glsl::exception(
		FCPPT_TEXT("Invalid int type!")
	);
}
