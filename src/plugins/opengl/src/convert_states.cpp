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


#include "../convert_states.hpp"
#include <sge/renderer/state/var.hpp>
#include <sge/exception.hpp>
#include <sge/text.hpp>

GLenum sge::ogl::convert_states(
	renderer::state::bool_::type const s)
{
	typedef renderer::state::traits<
		renderer::state::bool_type
	> rs;

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

GLenum sge::ogl::convert_states(
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

GLenum sge::ogl::convert_states(
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

GLenum sge::ogl::convert_states(
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

GLenum sge::ogl::convert_states(
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

GLenum sge::ogl::convert_states(
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

GLenum sge::ogl::convert_states(
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

GLenum sge::ogl::convert_states(
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

GLenum sge::ogl::convert_states(
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
