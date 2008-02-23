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


#include "../../../exception.hpp"
#include "../conversion_visitor.hpp"

GLenum sge::ogl::conversion_visitor::operator()(const bool_state::type s) const
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

GLenum sge::ogl::conversion_visitor::operator()(const cull_mode::type m) const
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

GLenum sge::ogl::conversion_visitor::operator()(const depth_func::type f) const
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

GLenum sge::ogl::conversion_visitor::operator()(const stencil_func::type f) const
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

GLenum sge::ogl::conversion_visitor::operator()(const fog_mode::type m) const
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

GLenum sge::ogl::conversion_visitor::operator()(const source_blend_func::type f) const
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

GLenum sge::ogl::conversion_visitor::operator()(const dest_blend_func::type f) const
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

GLenum sge::ogl::conversion_visitor::operator()(const draw_mode::type m) const
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



