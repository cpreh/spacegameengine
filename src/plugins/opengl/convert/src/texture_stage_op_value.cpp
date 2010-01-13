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


#include "../texture_stage_op_value.hpp"
#include <sge/exception.hpp>
#include <fcppt/text.hpp>

GLenum
sge::opengl::convert::texture_stage_value(
	renderer::texture_stage_op_value::type const value
)
{
	switch(value) {
	case renderer::texture_stage_op_value::arg0:
		return GL_REPLACE;
	case renderer::texture_stage_op_value::modulate:
	case renderer::texture_stage_op_value::modulate2x:
	case renderer::texture_stage_op_value::modulate4x:
		return GL_MODULATE;
	case renderer::texture_stage_op_value::add:
	case renderer::texture_stage_op_value::add2x:
	case renderer::texture_stage_op_value::add4x:
		return GL_ADD;
	case renderer::texture_stage_op_value::substract:
		return GL_SUBTRACT;
	case renderer::texture_stage_op_value::add_signed:
	case renderer::texture_stage_op_value::add_signed2x:
		return GL_ADD_SIGNED;
	case renderer::texture_stage_op_value::interpolate:
		return GL_INTERPOLATE;
	}

	throw exception(
		FCPPT_TEXT("Invalid texture_stage_op_value!")
	);
}
