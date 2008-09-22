/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2007  Carl Philipp Reh (sefi@s-e-f-i.de)

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


#include "../conversion.hpp"
#include <sge/renderer/state/var.hpp>
#include <sge/exception.hpp>
#include <sge/text.hpp>

GLenum sge::ogl::convert_cast(
	renderer::state::bool_::type const s)
{
	typedef renderer::state::traits<bool> rs;

	switch(s.state()) {
	case rs::enable_alpha_blending:
		return GL_BLEND;
	case rs::enable_lighting:
		return GL_LIGHTING;
	default:
		throw exception(
			SGE_TEXT("Invalid bool_state!"));
	}
}

GLenum sge::ogl::convert_cast(
	renderer::state::cull_mode::type const m)
{		
	switch(m) {
	case renderer::state::cull_mode::back:
		return GL_BACK;
	case renderer::state::cull_mode::front:
		return GL_FRONT;
	default:
		throw exception(
			SGE_TEXT("Invalid cull_mode!"));
	}
}

GLenum sge::ogl::convert_cast(
	renderer::state::depth_func::type const f)
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
	default:
		throw exception(
			SGE_TEXT("Invalid depth_func!"));
	}
}

GLenum sge::ogl::convert_cast(
	renderer::state::stencil_func::type const f)
{
	switch(f) {
	case renderer::state::stencil_func::never:
		return GL_NEVER;
	case renderer::state::stencil_func::less:
		return GL_LESS;
	case renderer::state::stencil_func::equal:
		return GL_EQUAL;
	case renderer::state::stencil_func::less_equal:
		return GL_LEQUAL;
	case renderer::state::stencil_func::greater:
		return GL_GREATER;
	case renderer::state::stencil_func::not_equal:
		return GL_NOTEQUAL;
	case renderer::state::stencil_func::greater_equal:
		return GL_GEQUAL;
	case renderer::state::stencil_func::always:
		return GL_ALWAYS;
	default:
		throw exception(
			SGE_TEXT("Invalid stencil_func!"));
	}
}

GLenum sge::ogl::convert_cast(
	renderer::state::alpha_func::type const f)
{
	switch(f) {
	case renderer::state::alpha_func::never:
		return GL_NEVER;
	case renderer::state::alpha_func::less:
		return GL_LESS;
	case renderer::state::alpha_func::equal:
		return GL_EQUAL;
	case renderer::state::alpha_func::less_equal:
		return GL_LEQUAL;
	case renderer::state::alpha_func::greater:
		return GL_GREATER;
	case renderer::state::alpha_func::not_equal:
		return GL_NOTEQUAL;
	case renderer::state::alpha_func::greater_equal:
		return GL_GEQUAL;
	case renderer::state::alpha_func::always:
		return GL_ALWAYS;
	default:
		throw exception(
			SGE_TEXT("Invalid alpha_func!"));
	}
}

GLenum sge::ogl::convert_cast(
	renderer::state::fog_mode::type const m)
{
	switch(m) {
	case renderer::state::fog_mode::linear:
		return GL_LINEAR;
	case renderer::state::fog_mode::exp:
		return GL_EXP;
	case renderer::state::fog_mode::exp2:
		return GL_EXP2;
	default:
		throw exception(
			SGE_TEXT("Invalid fog_mode!"));
	}
}

GLenum sge::ogl::convert_cast(
	renderer::state::source_blend_func::type const f)
{
	switch(f) {
	case renderer::state::source_blend_func::zero:
		return GL_ZERO;
	case renderer::state::source_blend_func::one:
		return GL_ONE;
	case renderer::state::source_blend_func::dest_color:
		return GL_DST_COLOR;
	case renderer::state::source_blend_func::inv_dest_color:
		return GL_ONE_MINUS_DST_COLOR;
	case renderer::state::source_blend_func::src_alpha:
		return GL_SRC_ALPHA;
	case renderer::state::source_blend_func::inv_src_alpha:
		return GL_ONE_MINUS_SRC_ALPHA;
	case renderer::state::source_blend_func::dest_alpha:
		return GL_DST_ALPHA;
	case renderer::state::source_blend_func::inv_dest_alpha:
		return GL_ONE_MINUS_DST_ALPHA;
	case renderer::state::source_blend_func::src_alpha_sat:
		return GL_SRC_ALPHA_SATURATE;
	default:
		throw exception(
			SGE_TEXT("Invalid source_blend_func!"));
	}
}

GLenum sge::ogl::convert_cast(
	renderer::state::dest_blend_func::type const f)
{
	switch(f) {
	case renderer::state::dest_blend_func::zero:
		return GL_ZERO;
	case renderer::state::dest_blend_func::one:
		return GL_ONE;
	case renderer::state::dest_blend_func::src_color:
		return GL_SRC_COLOR;
	case renderer::state::dest_blend_func::inv_src_color:
		return GL_ONE_MINUS_SRC_COLOR;
	case renderer::state::dest_blend_func::src_alpha:
		return GL_SRC_ALPHA;
	case renderer::state::dest_blend_func::inv_src_alpha:
		return GL_ONE_MINUS_SRC_ALPHA;
	case renderer::state::dest_blend_func::dest_alpha:
		return GL_DST_ALPHA;
	case renderer::state::dest_blend_func::inv_dest_alpha:
		return GL_ONE_MINUS_DST_ALPHA;
	default:
		throw exception(
			SGE_TEXT("Invalid dest_blend_func!"));
	}
}

GLenum sge::ogl::convert_cast(
	renderer::state::draw_mode::type const m)
{
	switch(m) {
	case renderer::state::draw_mode::point:
		return GL_POINT;
	case renderer::state::draw_mode::line:
		return GL_LINE;
	case renderer::state::draw_mode::fill:
		return GL_FILL;
	default:
		throw exception(
			SGE_TEXT("Invalid draw_mode!"));
	}
}

GLenum sge::ogl::convert_cast(
	renderer::nonindexed_primitive_type::type const t)
{
	switch(t) {
	case renderer::nonindexed_primitive_type::point:
		return GL_POINTS;
	case renderer::nonindexed_primitive_type::line_strip:
		return GL_LINE_STRIP;
	case renderer::nonindexed_primitive_type::triangle_strip:
		return GL_TRIANGLE_STRIP;
	case renderer::nonindexed_primitive_type::triangle_fan:
		return GL_TRIANGLE_FAN;
	case renderer::nonindexed_primitive_type::line_loop:
		return GL_LINE_LOOP;
	default:
		throw exception(
			SGE_TEXT("Invalid indexed_primitive_type!"));
	}
}

GLenum sge::ogl::convert_cast(
	renderer::indexed_primitive_type::type const t)
{
	switch(t) {
	case renderer::indexed_primitive_type::line:
		return GL_LINES;
	case renderer::indexed_primitive_type::triangle:
		return GL_TRIANGLES;
	default:
		throw exception(
			SGE_TEXT("Invalid nonindexed_primitive_type!"));
	}
}

GLenum sge::ogl::convert_cast(
	renderer::min_filter::type const arg)
{
	switch(arg) {
	case renderer::min_filter::point:
		return GL_NEAREST;
	case renderer::min_filter::linear:
		return GL_LINEAR;
	case renderer::min_filter::mipmap:
		return GL_LINEAR_MIPMAP_NEAREST;
	case renderer::min_filter::trilinear:
		return GL_LINEAR_MIPMAP_LINEAR;
	default:
		throw exception(
			SGE_TEXT("Invalid min_filter!"));
	}
}

GLenum sge::ogl::convert_cast(
	renderer::mag_filter::type const arg)
{
	switch(arg) {
	case renderer::mag_filter::point:
		return GL_NEAREST;
	case renderer::mag_filter::linear:
		return GL_LINEAR;
	default:
		throw exception(
			SGE_TEXT("Invalid mag_filter!"));
	}
}

GLenum sge::ogl::convert_cast(
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

GLenum sge::ogl::convert_cast(
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

GLenum sge::ogl::convert_cast(
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

GLenum sge::ogl::convert_cast(
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

GLuint sge::ogl::convert_resource_flags(
	renderer::resource_flag_t const f)
{
	return (f & renderer::resource_flags::dynamic)
		? GL_DYNAMIC_DRAW
		: GL_STATIC_DRAW;
}

GLenum sge::ogl::convert_fog_float_state(
	renderer::state::float_::type const s)
{
	typedef renderer::state::traits<float> rs;
	switch(s.state()) {
	case rs::fog_start:
		return GL_FOG_START;
	case rs::fog_end:
		return GL_FOG_END;
	case rs::fog_density:
		return GL_FOG_DENSITY;
	default:
		throw exception(
			SGE_TEXT("Invalid fog float_state!"));
	}
}

GLenum sge::ogl::convert_clear_bit(
	renderer::state::bool_::type const s)
{
	typedef renderer::state::traits<bool> rs;
	switch(s.state()) {
	case rs::clear_backbuffer:
		return GL_COLOR_BUFFER_BIT;
	case rs::clear_zbuffer:
		return GL_DEPTH_BUFFER_BIT;
	case rs::clear_stencil:
		return GL_STENCIL_BUFFER_BIT;
	default:
		throw exception(
			SGE_TEXT("Invalid bool_state in convert_clear_bit()!"));
	}
}
