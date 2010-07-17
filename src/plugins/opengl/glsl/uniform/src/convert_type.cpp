/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2009 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#include "../convert_type.hpp"
#include <sge/renderer/glsl/exception.hpp>
#include <fcppt/text.hpp>

template<>
sge::renderer::glsl::uniform::int_value_type::type
sge::opengl::glsl::uniform::convert_type(
	element_type::type const _type
)
{
	namespace et = sge::opengl::glsl::uniform::element_type;
	namespace ivt = sge::renderer::glsl::uniform::int_value_type;

	switch(_type)
	{
	case et::int1:
		return ivt::int1;
	case et::int2:
		return ivt::int2;
	case et::int3:
		return ivt::int3;
	case et::int4:
		return ivt::int4;
	case et::nothing:
	case et::float1:
	case et::float2:
	case et::float3:
	case et::float4:
	case et::matrix2x2:
	case et::matrix3x3:
	case et::matrix4x4:
	case et::matrix2x3:
	case et::matrix3x2:
	case et::matrix2x4:
	case et::matrix4x2:
	case et::matrix3x4:
	case et::matrix4x3:
		break;
	}

	throw sge::renderer::glsl::exception(
		FCPPT_TEXT("Invalid int element!")
	);
}

template<>
sge::renderer::glsl::uniform::float_value_type::type
sge::opengl::glsl::uniform::convert_type(
	element_type::type const _type
)
{
	namespace et = sge::opengl::glsl::uniform::element_type;
	namespace fvt = sge::renderer::glsl::uniform::float_value_type;

	switch(_type)
	{
	case et::float1:
		return fvt::float1;
	case et::float2:
		return fvt::float2;
	case et::float3:
		return fvt::float3;
	case et::float4:
		return fvt::float4;
	case et::matrix2x2:
		return fvt::matrix2x2;
	case et::matrix3x3:
		return fvt::matrix3x3;
	case et::matrix4x4:
		return fvt::matrix4x4;
	case et::matrix2x3:
		return fvt::matrix2x3;
	case et::matrix3x2:
		return fvt::matrix3x2;
	case et::matrix2x4:
		return fvt::matrix2x4;
	case et::matrix4x2:
		return fvt::matrix4x2;
	case et::matrix3x4:
		return fvt::matrix3x4;
	case et::matrix4x3:
		return fvt::matrix4x3;
	case et::nothing:
	case et::int1:
	case et::int2:
	case et::int3:
	case et::int4:
		break;
	}

	throw sge::renderer::glsl::exception(
		FCPPT_TEXT("Invalid float type!")
	);
}
