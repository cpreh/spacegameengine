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


#include <sge/renderer/state/default.hpp>
#include <sge/renderer/state/list.hpp>
#include <sge/renderer/state/var.hpp>
#include <sge/renderer/state/trampoline.hpp>
#include <sge/image/colors.hpp>

sge::renderer::state::list const
sge::renderer::state::default_()
{
	return
		state::list
			(int_::stencil_clear_val = 0)
			(int_::stencil_ref = 0)
			(uint::stencil_mask = 0)
			(float_::zbuffer_clear_val = 0.f)
			(float_::fog_start = 0.f)
			(float_::fog_end = 0.f)
			(float_::fog_density = 0.f)
			(float_::alpha_test_ref = 0.f)
			(bool_::clear_zbuffer = false)
			(bool_::clear_backbuffer = false)
			(bool_::clear_stencil = false)
			(bool_::enable_alpha_blending = false)
			(bool_::enable_lighting = false)
			(bool_::enable_multi_sampling = false)
			(bool_::write_to_zbuffer = true)
			(color::clear_color = image::colors::white())
			(color::ambient_light_color = image::colors::white())
			(color::fog_color = image::colors::black())
			(cull_mode::off)
			(depth_func::off)
			(stencil_func::off)
			(alpha_func::off)
			(fog_mode::off)
			(draw_mode::fill)
			(source_blend_func::one)
			(dest_blend_func::zero)
		;
}
