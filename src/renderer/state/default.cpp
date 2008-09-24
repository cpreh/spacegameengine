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


#include <sge/renderer/state/default.hpp>
#include <sge/renderer/state/list.hpp>
#include <sge/renderer/state/states.hpp>
#include <sge/renderer/state/var.hpp>
#include <sge/renderer/colors.hpp>

sge::renderer::state::list const
sge::renderer::state::default_()
{
	static const list l(
		list
			(int_::stencil_clear_val = 0)
			(int_::stencil_ref = 0)
			(uint_::stencil_mask = 0)
			(float_::zbuffer_clear_val = 0)
			(float_::fog_start = 0)
			(float_::fog_end = 0)
			(float_::fog_density = 0)
			(float_::alpha_test_ref = 0)
			(bool_::clear_zbuffer = false)
			(bool_::clear_backbuffer = true)
			(bool_::clear_stencil = false)
			(bool_::enable_alpha_blending = false)
			(bool_::enable_lighting = false)
			(color_::clear_color = colors::red())
			(color_::ambient_light_color = colors::white())
			(color_::fog_color = colors::black())
			(cull_mode::off)
			(depth_func::off)
			(stencil_func::off)
			(alpha_func::off)
			(fog_mode::off)
			(draw_mode::fill)
			(source_blend_func::src_alpha)
			(dest_blend_func::inv_src_alpha)
	);
	return l;
}
