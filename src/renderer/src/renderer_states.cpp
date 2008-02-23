/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2008       Simon Stienen    (s.stienen@slashlife.org)

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

#include "../renderer_states.hpp"



////////////////////////////////////////////////////////////////////////////////
// int_states
//

sge::int_state::type
	sge::int_state::stencil_clear_val(
		sge::renderer_state_var_traits<int>::stencil_clear_val
	);



////////////////////////////////////////////////////////////////////////////////
// float_states
//

sge::float_state::type
	sge::float_state::zbuffer_clear_val(
		sge::renderer_state_var_traits<float>::zbuffer_clear_val
	),
	sge::float_state::fog_start(
		sge::renderer_state_var_traits<float>::fog_start
	),
	sge::float_state::fog_end(
		sge::renderer_state_var_traits<float>::fog_end
	),
	sge::float_state::fog_density(
		sge::renderer_state_var_traits<float>::fog_density
	);



////////////////////////////////////////////////////////////////////////////////
// bool_states
//

sge::bool_state::type
	sge::bool_state::clear_zbuffer(
		sge::renderer_state_var_traits<bool>::clear_zbuffer
	),
	sge::bool_state::clear_backbuffer(
		sge::renderer_state_var_traits<bool>::clear_backbuffer
	),
	sge::bool_state::clear_stencil(
		sge::renderer_state_var_traits<bool>::clear_stencil
	),
	sge::bool_state::enable_alpha_blending(
		sge::renderer_state_var_traits<bool>::enable_alpha_blending
	),
	sge::bool_state::enable_zbuffer(
		sge::renderer_state_var_traits<bool>::enable_zbuffer
	),
	sge::bool_state::enable_lighting(
		sge::renderer_state_var_traits<bool>::enable_lighting
	);



////////////////////////////////////////////////////////////////////////////////
// color_states
//

sge::color_state::type
	sge::color_state::clear_color(
		sge::renderer_state_var_traits<sge::color>::clear_color
	),
	sge::color_state::ambient_light_color(
		sge::renderer_state_var_traits<sge::color>::ambient_light_color
	),
	sge::color_state::fog_color(
		sge::renderer_state_var_traits<sge::color>::fog_color
	);



////////////////////////////////////////////////////////////////////////////////
// cull_modes
//

const sge::cull_mode::type
	sge::cull_mode::off(
		sge::renderer_state_var_traits<sge::renderer_state_cull_mode_type::type>::singular,
		sge::renderer_state_cull_mode_type::off
	),
	sge::cull_mode::back(
		sge::renderer_state_var_traits<sge::renderer_state_cull_mode_type::type>::singular,
		sge::renderer_state_cull_mode_type::back
	),
	sge::cull_mode::front(
		sge::renderer_state_var_traits<sge::renderer_state_cull_mode_type::type>::singular,
		sge::renderer_state_cull_mode_type::front
	);



////////////////////////////////////////////////////////////////////////////////
// depth_funcs
//

const sge::depth_func::type
	sge::depth_func::never(
		sge::renderer_state_var_traits<sge::renderer_state_depth_func_type::type>::singular,
		sge::renderer_state_depth_func_type::never
	),
	sge::depth_func::less(
		sge::renderer_state_var_traits<sge::renderer_state_depth_func_type::type>::singular,
		sge::renderer_state_depth_func_type::less
	),
	sge::depth_func::equal(
		sge::renderer_state_var_traits<sge::renderer_state_depth_func_type::type>::singular,
		sge::renderer_state_depth_func_type::equal
	),
	sge::depth_func::less_equal(
		sge::renderer_state_var_traits<sge::renderer_state_depth_func_type::type>::singular,
		sge::renderer_state_depth_func_type::less_equal
	),
	sge::depth_func::greater(
		sge::renderer_state_var_traits<sge::renderer_state_depth_func_type::type>::singular,
		sge::renderer_state_depth_func_type::greater
	),
	sge::depth_func::not_equal(
		sge::renderer_state_var_traits<sge::renderer_state_depth_func_type::type>::singular,
		sge::renderer_state_depth_func_type::not_equal
	),
	sge::depth_func::greater_equal(
		sge::renderer_state_var_traits<sge::renderer_state_depth_func_type::type>::singular,
		sge::renderer_state_depth_func_type::greater_equal
	),
	sge::depth_func::always(
		sge::renderer_state_var_traits<sge::renderer_state_depth_func_type::type>::singular,
		sge::renderer_state_depth_func_type::always
	);



////////////////////////////////////////////////////////////////////////////////
// stencil_funcs
//

const sge::stencil_func::type
	sge::stencil_func::off(
		sge::renderer_state_var_traits<sge::renderer_state_stencil_func_type::type>::singular,
		sge::renderer_state_stencil_func_type::off
	),
	sge::stencil_func::never(
		sge::renderer_state_var_traits<sge::renderer_state_stencil_func_type::type>::singular,
		sge::renderer_state_stencil_func_type::never
	),
	sge::stencil_func::less(
		sge::renderer_state_var_traits<sge::renderer_state_stencil_func_type::type>::singular,
		sge::renderer_state_stencil_func_type::less
	),
	sge::stencil_func::equal(
		sge::renderer_state_var_traits<sge::renderer_state_stencil_func_type::type>::singular,
		sge::renderer_state_stencil_func_type::equal
	),
	sge::stencil_func::less_equal(
		sge::renderer_state_var_traits<sge::renderer_state_stencil_func_type::type>::singular,
		sge::renderer_state_stencil_func_type::less_equal
	),
	sge::stencil_func::greater(
		sge::renderer_state_var_traits<sge::renderer_state_stencil_func_type::type>::singular,
		sge::renderer_state_stencil_func_type::greater
	),
	sge::stencil_func::not_equal(
		sge::renderer_state_var_traits<sge::renderer_state_stencil_func_type::type>::singular,
		sge::renderer_state_stencil_func_type::not_equal
	),
	sge::stencil_func::greater_equal(
		sge::renderer_state_var_traits<sge::renderer_state_stencil_func_type::type>::singular,
		sge::renderer_state_stencil_func_type::greater_equal
	),
	sge::stencil_func::always(
		sge::renderer_state_var_traits<sge::renderer_state_stencil_func_type::type>::singular,
		sge::renderer_state_stencil_func_type::always
	);



////////////////////////////////////////////////////////////////////////////////
// fog_modes
//

const sge::fog_mode::type
	sge::fog_mode::off(
		sge::renderer_state_var_traits<sge::renderer_state_fog_mode_type::type>::singular,
		sge::renderer_state_fog_mode_type::off
	),
	sge::fog_mode::linear(
		sge::renderer_state_var_traits<sge::renderer_state_fog_mode_type::type>::singular,
		sge::renderer_state_fog_mode_type::linear
	),
	sge::fog_mode::exp(
		sge::renderer_state_var_traits<sge::renderer_state_fog_mode_type::type>::singular,
		sge::renderer_state_fog_mode_type::exp
	),
	sge::fog_mode::exp2(
		sge::renderer_state_var_traits<sge::renderer_state_fog_mode_type::type>::singular,
		sge::renderer_state_fog_mode_type::exp2
	);



////////////////////////////////////////////////////////////////////////////////
// draw_modes
//

const sge::draw_mode::type
	sge::draw_mode::point(
		sge::renderer_state_var_traits<sge::renderer_state_draw_mode_type::type>::singular,
		sge::renderer_state_draw_mode_type::point
	),
	sge::draw_mode::line(
		sge::renderer_state_var_traits<sge::renderer_state_draw_mode_type::type>::singular,
		sge::renderer_state_draw_mode_type::line
	),
	sge::draw_mode::fill(
		sge::renderer_state_var_traits<sge::renderer_state_draw_mode_type::type>::singular,
		sge::renderer_state_draw_mode_type::fill
	);



////////////////////////////////////////////////////////////////////////////////
// source_blend_funcs
//

const sge::source_blend_func::type
	sge::source_blend_func::zero(
		sge::renderer_state_var_traits<sge::renderer_state_source_blend_func_type::type>::singular,
		sge::renderer_state_source_blend_func_type::zero
	),
	sge::source_blend_func::one(
		sge::renderer_state_var_traits<sge::renderer_state_source_blend_func_type::type>::singular,
		sge::renderer_state_source_blend_func_type::one
	),
	sge::source_blend_func::dest_color(
		sge::renderer_state_var_traits<sge::renderer_state_source_blend_func_type::type>::singular,
		sge::renderer_state_source_blend_func_type::dest_color
	),
	sge::source_blend_func::inv_dest_color(
		sge::renderer_state_var_traits<sge::renderer_state_source_blend_func_type::type>::singular,
		sge::renderer_state_source_blend_func_type::inv_dest_color
	),
	sge::source_blend_func::src_alpha(
		sge::renderer_state_var_traits<sge::renderer_state_source_blend_func_type::type>::singular,
		sge::renderer_state_source_blend_func_type::src_alpha
	),
	sge::source_blend_func::inv_src_alpha(
		sge::renderer_state_var_traits<sge::renderer_state_source_blend_func_type::type>::singular,
		sge::renderer_state_source_blend_func_type::inv_src_alpha
	),
	sge::source_blend_func::dest_alpha(
		sge::renderer_state_var_traits<sge::renderer_state_source_blend_func_type::type>::singular,
		sge::renderer_state_source_blend_func_type::dest_alpha
	),
	sge::source_blend_func::inv_dest_alpha(
		sge::renderer_state_var_traits<sge::renderer_state_source_blend_func_type::type>::singular,
		sge::renderer_state_source_blend_func_type::inv_dest_alpha
	),
	sge::source_blend_func::src_alpha_sat(
		sge::renderer_state_var_traits<sge::renderer_state_source_blend_func_type::type>::singular,
		sge::renderer_state_source_blend_func_type::src_alpha_sat
	);



////////////////////////////////////////////////////////////////////////////////
// dest_blend_funcs
//

const sge::dest_blend_func::type
	sge::dest_blend_func::zero(
		sge::renderer_state_var_traits<sge::renderer_state_dest_blend_func_type::type>::singular,
		sge::renderer_state_dest_blend_func_type::zero
	),
	sge::dest_blend_func::one(
		sge::renderer_state_var_traits<sge::renderer_state_dest_blend_func_type::type>::singular,
		sge::renderer_state_dest_blend_func_type::one
	),
	sge::dest_blend_func::src_color(
		sge::renderer_state_var_traits<sge::renderer_state_dest_blend_func_type::type>::singular,
		sge::renderer_state_dest_blend_func_type::src_color
	),
	sge::dest_blend_func::inv_src_color(
		sge::renderer_state_var_traits<sge::renderer_state_dest_blend_func_type::type>::singular,
		sge::renderer_state_dest_blend_func_type::inv_src_color
	),
	sge::dest_blend_func::src_alpha(
		sge::renderer_state_var_traits<sge::renderer_state_dest_blend_func_type::type>::singular,
		sge::renderer_state_dest_blend_func_type::src_alpha
	),
	sge::dest_blend_func::inv_src_alpha(
		sge::renderer_state_var_traits<sge::renderer_state_dest_blend_func_type::type>::singular,
		sge::renderer_state_dest_blend_func_type::inv_src_alpha
	),
	sge::dest_blend_func::dest_alpha(
		sge::renderer_state_var_traits<sge::renderer_state_dest_blend_func_type::type>::singular,
		sge::renderer_state_dest_blend_func_type::dest_alpha
	),
	sge::dest_blend_func::inv_dest_alpha(
		sge::renderer_state_var_traits<sge::renderer_state_dest_blend_func_type::type>::singular,
		sge::renderer_state_dest_blend_func_type::inv_dest_alpha
	);
