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


#include "../element_columns.hpp"
#include <sge/renderer/glsl/exception.hpp>
#include <fcppt/text.hpp>

GLsizei
sge::opengl::glsl::uniform::element_columns(
	sge::renderer::glsl::uniform::float_value_type::type const _type
)
{
	namespace fv = sge::renderer::glsl::uniform::float_value_type;

	switch(
		_type
	)
	{
	case fv::matrix2x2:
	case fv::matrix2x3:
	case fv::matrix2x4:
		return 2;
	case fv::matrix3x2:
	case fv::matrix3x3:
	case fv::matrix3x4:
		return 3;
	case fv::matrix4x2:
	case fv::matrix4x3:
	case fv::matrix4x4:
		return 4;
	case fv::float1:
	case fv::float2:
	case fv::float3:
	case fv::float4:
		break;
	}

	throw sge::renderer::glsl::exception(
		FCPPT_TEXT("Invalid matrix type in glsl element_columns!")
	);
}
