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


#include <sge/renderer/default_states.hpp>
#include <sge/renderer/color.hpp>
#include <sge/renderer/colors.hpp>

sge::renderer::state_list const
sge::renderer::default_states()
{
	static const state_list list(
		state_list
			(int_state::stencil_clear_val = 0)
			(float_state::zbuffer_clear_val = 0)
			(float_state::fog_start = 0)
			(float_state::fog_end = 0)
			(float_state::fog_density = 0)
			(bool_state::clear_zbuffer = false)
			(bool_state::clear_backbuffer = true)
			(bool_state::clear_stencil = false)
			(bool_state::enable_alpha_blending = false)
			(bool_state::enable_lighting = false)
			(color_state::clear_color = colors::black())
			(color_state::ambient_light_color = colors::white())
			(color_state::fog_color = colors::black())
			(cull_mode::off)
			(depth_func::off)
			(stencil_func::off)
			(alpha_func::off)
			(fog_mode::off)
			(draw_mode::fill)
			(source_blend_func::src_alpha)
			(dest_blend_func::inv_src_alpha)
	);
	return list;
}
