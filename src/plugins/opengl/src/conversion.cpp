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
#include <sge/exception.hpp>

GLenum sge::ogl::convert_cast(const bool_state::type s)
{
	typedef renderer_state_var_traits<bool> rs;

	switch(s.state_id) {
	case rs::enable_alpha_blending:
		return GL_BLEND;
	case rs::enable_lighting:
		return GL_LIGHTING;
	default:
		throw exception(SGE_TEXT("Invalid bool_state!"));
	}
}

GLenum sge::ogl::convert_cast(const cull_mode::type m)
{		
	switch(m.value()) {
	case renderer_state_cull_mode_type::back:
		return GL_BACK;
	case renderer_state_cull_mode_type::front:
		return GL_FRONT;
	default:
		throw exception(SGE_TEXT("Invalid cull_mode!"));
	}
}

GLenum sge::ogl::convert_cast(const depth_func::type f)
{
	switch(f.value()) {
	case renderer_state_depth_func_type::never:
		return GL_NEVER;
	case renderer_state_depth_func_type::less:
		return GL_LESS;
	case renderer_state_depth_func_type::equal:
		return GL_EQUAL;
	case renderer_state_depth_func_type::less_equal:
		return GL_LEQUAL;
	case renderer_state_depth_func_type::greater:
		return GL_GREATER;
	case renderer_state_depth_func_type::not_equal:
		return GL_NOTEQUAL;
	case renderer_state_depth_func_type::greater_equal:
		return GL_GEQUAL;
	case renderer_state_depth_func_type::always:
		return GL_ALWAYS;
	default:
		throw exception(SGE_TEXT("Invalid depth_func!"));
	}
}

GLenum sge::ogl::convert_cast(const stencil_func::type f)
{
	switch(f.value()) {
	case renderer_state_stencil_func_type::never:
		return GL_NEVER;
	case renderer_state_stencil_func_type::less:
		return GL_LESS;
	case renderer_state_stencil_func_type::equal:
		return GL_EQUAL;
	case renderer_state_stencil_func_type::less_equal:
		return GL_LEQUAL;
	case renderer_state_stencil_func_type::greater:
		return GL_GREATER;
	case renderer_state_stencil_func_type::not_equal:
		return GL_NOTEQUAL;
	case renderer_state_stencil_func_type::greater_equal:
		return GL_GEQUAL;
	case renderer_state_stencil_func_type::always:
		return GL_ALWAYS;
	default:
		throw exception(SGE_TEXT("Invalid stencil_func!"));
	}
}

GLenum sge::ogl::convert_cast(const fog_mode::type m)
{
	switch(m.value()) {
	case renderer_state_fog_mode_type::linear:
		return GL_LINEAR;
	case renderer_state_fog_mode_type::exp:
		return GL_EXP;
	case renderer_state_fog_mode_type::exp2:
		return GL_EXP2;
	default:
		throw exception(SGE_TEXT("Invalid fog_mode!"));
	}
}

GLenum sge::ogl::convert_cast(const source_blend_func::type f)
{
	switch(f.value()) {
	case renderer_state_source_blend_func_type::zero:
		return GL_ZERO;
	case renderer_state_source_blend_func_type::one:
		return GL_ONE;
	case renderer_state_source_blend_func_type::dest_color:
		return GL_DST_COLOR;
	case renderer_state_source_blend_func_type::inv_dest_color:
		return GL_ONE_MINUS_DST_COLOR;
	case renderer_state_source_blend_func_type::src_alpha:
		return GL_SRC_ALPHA;
	case renderer_state_source_blend_func_type::inv_src_alpha:
		return GL_ONE_MINUS_SRC_ALPHA;
	case renderer_state_source_blend_func_type::dest_alpha:
		return GL_DST_ALPHA;
	case renderer_state_source_blend_func_type::inv_dest_alpha:
		return GL_ONE_MINUS_DST_ALPHA;
	case renderer_state_source_blend_func_type::src_alpha_sat:
		return GL_SRC_ALPHA_SATURATE;
	default:
		throw exception(SGE_TEXT("Invalid source_blend_func!"));
	}
}

GLenum sge::ogl::convert_cast(const dest_blend_func::type f)
{
	switch(f.value()) {
	case renderer_state_dest_blend_func_type::zero:
		return GL_ZERO;
	case renderer_state_dest_blend_func_type::one:
		return GL_ONE;
	case renderer_state_dest_blend_func_type::src_color:
		return GL_SRC_COLOR;
	case renderer_state_dest_blend_func_type::inv_src_color:
		return GL_ONE_MINUS_SRC_COLOR;
	case renderer_state_dest_blend_func_type::src_alpha:
		return GL_SRC_ALPHA;
	case renderer_state_dest_blend_func_type::inv_src_alpha:
		return GL_ONE_MINUS_SRC_ALPHA;
	case renderer_state_dest_blend_func_type::dest_alpha:
		return GL_DST_ALPHA;
	case renderer_state_dest_blend_func_type::inv_dest_alpha:
		return GL_ONE_MINUS_DST_ALPHA;
	default:
		throw exception(SGE_TEXT("Invalid dest_blend_func!"));
	}
}

GLenum sge::ogl::convert_cast(const draw_mode::type m)
{
	switch(m.value()) {
	case renderer_state_draw_mode_type::point:
		return GL_POINT;
	case renderer_state_draw_mode_type::line:
		return GL_LINE;
	case renderer_state_draw_mode_type::fill:
		return GL_FILL;
	default:
		throw exception(SGE_TEXT("Invalid draw_mode!"));
	}
}



GLuint sge::ogl::convert_cast(const lock_flag_t& f)
{
	switch(f) {
	case lock_flags::readonly:
		return GL_READ_ONLY;
	case lock_flags::writeonly:
		return GL_WRITE_ONLY;
	case lock_flags::readwrite:
		return GL_READ_WRITE;
	default:
		throw exception(SGE_TEXT("Invalid lock_flags!"));
	}
}

GLenum sge::ogl::convert_cast(const nonindexed_primitive_type::type& t)
{
	switch(t) {
	case nonindexed_primitive_type::point:
		return GL_POINTS;
	case nonindexed_primitive_type::line_strip:
		return GL_LINE_STRIP;
	case nonindexed_primitive_type::triangle_strip:
		return GL_TRIANGLE_STRIP;
	case nonindexed_primitive_type::triangle_fan:
		return GL_TRIANGLE_FAN;
	case nonindexed_primitive_type::line_loop:
		return GL_LINE_LOOP;
	default:
		throw exception(SGE_TEXT("Invalid indexed_primitive_type!"));
	}
}

GLenum sge::ogl::convert_cast(const indexed_primitive_type::type& t)
{
	switch(t) {
	case indexed_primitive_type::line:
		return GL_LINES;
	case indexed_primitive_type::triangle:
		return GL_TRIANGLES;
	default:
		throw exception(SGE_TEXT("Invalid nonindexed_primitive_type!"));
	}
}

GLenum sge::ogl::convert_cast(const min_filter::type& arg)
{
	switch(arg) {
	case min_filter::point:
		return GL_NEAREST;
	case min_filter::linear:
		return GL_LINEAR;
	case min_filter::mipmap:
		return GL_LINEAR_MIPMAP_NEAREST;
	case min_filter::trilinear:
		return GL_LINEAR_MIPMAP_LINEAR;
	default:
		throw exception(SGE_TEXT("Invalid min_filter!"));
	}
}

GLenum sge::ogl::convert_cast(const mag_filter::type& arg)
{
	switch(arg) {
	case mag_filter::point:
		return GL_NEAREST;
	case mag_filter::linear:
		return GL_LINEAR;
	default:
		throw exception(SGE_TEXT("Invalid mag_filter!"));
	}
}

namespace
{

typedef boost::array<GLenum, sge::cube_side::num_elements> cube_side_array;
const cube_side_array cube_sides =
{
	{
#ifdef SGE_OPENGL_CUBE_TEXTURE
		GL_TEXTURE_CUBE_MAP_POSITIVE_Z,
		GL_TEXTURE_CUBE_MAP_NEGATIVE_Z,
		GL_TEXTURE_CUBE_MAP_NEGATIVE_X,
		GL_TEXTURE_CUBE_MAP_POSITIVE_X,
		GL_TEXTURE_CUBE_MAP_POSITIVE_Y,
		GL_TEXTURE_CUBE_MAP_NEGATIVE_Y
#elif SGE_OPENGL_CUBE_TEXTURE_ARB
		GL_TEXTURE_CUBE_MAP_POSITIVE_Z_ARB,
		GL_TEXTURE_CUBE_MAP_NEGATIVE_Z_ARB,
		GL_TEXTURE_CUBE_MAP_NEGATIVE_X_ARB,
		GL_TEXTURE_CUBE_MAP_POSITIVE_X_ARB,
		GL_TEXTURE_CUBE_MAP_POSITIVE_Y_ARB,
		GL_TEXTURE_CUBE_MAP_NEGATIVE_Y_ARB
#endif
	}
};

}

#ifdef SGE_OPENGL_HAVE_CUBE_TEXTURE
GLenum sge::ogl::convert_cast(const cube_side::type& s)
{
	const cube_side_array::size_type pos = static_cast<cube_side_array::size_type>(s);
	if(pos >= cube_sides.size())
		throw exception(SGE_TEXT("Invalid cube_side!"));

	return cube_sides[pos];
}
#endif

GLenum sge::ogl::convert_cast(const texture_stage_op::type& op)
{
	switch(op) {
	case texture_stage_op::color:
		return GL_COMBINE_RGB;
	case texture_stage_op::alpha:
		return GL_COMBINE_ALPHA;
	default:
		throw exception(SGE_TEXT("Invalid texture_stage_op!"));
	}
}

GLenum sge::ogl::convert_cast(const texture_stage_op_value::type& value)
{
	switch(value) {
	case texture_stage_op_value::arg0:
		return GL_REPLACE;
	case texture_stage_op_value::modulate:
	case texture_stage_op_value::modulate2x:
	case texture_stage_op_value::modulate4x:
		return GL_MODULATE;
	case texture_stage_op_value::add:
	case texture_stage_op_value::add2x:
	case texture_stage_op_value::add4x:
		return GL_ADD;
	case texture_stage_op_value::substract:
		return GL_SUBTRACT;
	case texture_stage_op_value::add_signed:
	case texture_stage_op_value::add_signed2x:
		return GL_ADD_SIGNED;
	case texture_stage_op_value::interpolate:
		return GL_INTERPOLATE;
	default:
		throw exception(SGE_TEXT("Invalid texture_stage_op_value!"));
	}
}

GLenum sge::ogl::convert_cast(const texture_stage_arg::type& arg)
{
	switch(arg) {
	case texture_stage_arg::rgb0:
		return GL_SOURCE0_RGB;
	case texture_stage_arg::rgb1:
		return GL_SOURCE1_RGB;
	case texture_stage_arg::rgb2:
		return GL_SOURCE2_RGB;
	case texture_stage_arg::alpha0:
		return GL_SOURCE0_ALPHA;
	case texture_stage_arg::alpha1:
		return GL_SOURCE1_ALPHA;
	case texture_stage_arg::alpha2:
		return GL_SOURCE2_ALPHA;
	default:
		throw exception(SGE_TEXT("Invalid texture_stage_arg!"));
	}
}

GLenum sge::ogl::convert_cast(const texture_stage_arg_value::type& value)
{
	switch(value) {
	case texture_stage_arg_value::current:
		return GL_PRIMARY_COLOR;
	case texture_stage_arg_value::texture:
		return GL_TEXTURE;
	case texture_stage_arg_value::constant:
		return GL_CONSTANT;
	default:
		throw exception(SGE_TEXT("Invalid texture_stage_arg_value!"));
	}
}

GLuint sge::ogl::convert_resource_flags(const resource_flag_t f)
{
	return (f & resource_flags::dynamic)
		? GL_DYNAMIC_DRAW
		: GL_STATIC_DRAW;
}

GLenum sge::ogl::convert_fog_float_state(const float_state::type s)
{
	typedef renderer_state_var_traits<float> rs;
	switch(s.state_id) {
	case rs::fog_start:
		return GL_FOG_START;
	case rs::fog_end:
		return GL_FOG_END;
	case rs::fog_density:
		return GL_FOG_DENSITY;
	default:
		throw exception(SGE_TEXT("Invalid fog float_state!"));
	}
}

GLenum sge::ogl::convert_clear_bit(const bool_state::type s)
{
	typedef renderer_state_var_traits<bool> rs;
	switch(s.state_id) {
	case rs::clear_backbuffer:
		return GL_COLOR_BUFFER_BIT;
	case rs::clear_zbuffer:
		return GL_DEPTH_BUFFER_BIT;
	case rs::clear_stencil:
		return GL_STENCIL_BUFFER_BIT;
	default:
		throw exception(SGE_TEXT("Invalid bool_state in convert_clear_bit()!"));
	}
}
