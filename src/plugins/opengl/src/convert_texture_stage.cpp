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



#include "../convert_texture_stage.hpp"
#include <sge/exception.hpp>
#include <sge/text.hpp>

GLenum
sge::ogl::convert_texture_stage(
	renderer::texture_stage_op::type const op)
{
	switch(op) {
	case renderer::texture_stage_op::color:
		return GL_COMBINE_RGB;
	case renderer::texture_stage_op::alpha:
		return GL_COMBINE_ALPHA;
	default:
		throw exception(
			SGE_TEXT("Invalid texture_stage_op!"));
	}
}

GLenum
sge::ogl::convert_texture_stage(
	renderer::texture_stage_op_value::type const value)
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
	default:
		throw exception(
			SGE_TEXT("Invalid texture_stage_op_value!"));
	}
}

GLenum
sge::ogl::convert_texture_stage(
	renderer::texture_stage_arg::type const arg)
{
	switch(arg) {
	case renderer::texture_stage_arg::rgb0:
		return GL_SOURCE0_RGB;
	case renderer::texture_stage_arg::rgb1:
		return GL_SOURCE1_RGB;
	case renderer::texture_stage_arg::rgb2:
		return GL_SOURCE2_RGB;
	case renderer::texture_stage_arg::alpha0:
		return GL_SOURCE0_ALPHA;
	case renderer::texture_stage_arg::alpha1:
		return GL_SOURCE1_ALPHA;
	case renderer::texture_stage_arg::alpha2:
		return GL_SOURCE2_ALPHA;
	default:
		throw exception(
			SGE_TEXT("Invalid texture_stage_arg!"));
	}
}

GLenum
sge::ogl::convert_texture_stage(
	renderer::texture_stage_arg_value::type const value)
{
	switch(value) {
	case renderer::texture_stage_arg_value::current:
		return GL_PRIMARY_COLOR;
	case renderer::texture_stage_arg_value::texture:
		return GL_TEXTURE;
	case renderer::texture_stage_arg_value::constant:
		return GL_CONSTANT;
	default:
		throw exception(
			SGE_TEXT("Invalid texture_stage_arg_value!"));
	}
}
