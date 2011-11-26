/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2011 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#include <sge/image/colors.hpp>
#include <sge/renderer/state/alpha_func.hpp>
#include <sge/renderer/state/bool.hpp>
#include <sge/renderer/state/color.hpp>
#include <sge/renderer/state/cull_mode.hpp>
#include <sge/renderer/state/default.hpp>
#include <sge/renderer/state/depth_func.hpp>
#include <sge/renderer/state/dest_blend_func.hpp>
#include <sge/renderer/state/draw_mode.hpp>
#include <sge/renderer/state/float.hpp>
#include <sge/renderer/state/fog_mode.hpp>
#include <sge/renderer/state/int.hpp>
#include <sge/renderer/state/list.hpp>
#include <sge/renderer/state/source_blend_func.hpp>
#include <sge/renderer/state/stencil_op.hpp>
#include <sge/renderer/state/trampoline.hpp>
#include <sge/renderer/state/uint.hpp>
#include <sge/renderer/state/var.hpp>


sge::renderer::state::list const
sge::renderer::state::default_()
{
	return
		state::list
			(int_::stencil_buffer_clear_val = 0)
			(int_::stencil_ref = 0)
			(uint::stencil_mask = ~0u)
			(uint::stencil_write_mask = ~0u)
			(float_::depth_buffer_clear_val = 0.f)
			(float_::fog_start = 0.f)
			(float_::fog_end = 0.f)
			(float_::fog_density = 0.f)
			(float_::alpha_test_ref = 0.f)
			(bool_::clear_depth_buffer = false)
			(bool_::clear_back_buffer = false)
			(bool_::clear_stencil_buffer = false)
			(bool_::enable_alpha_blending = false)
			(bool_::enable_scissor_test = false)
			(bool_::enable_lighting = false)
			(bool_::enable_point_sprites = false)
			(bool_::write_to_depth_buffer = true)
			(bool_::write_alpha = true)
			(bool_::write_blue = true)
			(bool_::write_green = true)
			(bool_::write_red = true)
			(color::back_buffer_clear_color = image::colors::white())
			(color::ambient_light_color = image::colors::white())
			(color::fog_color = image::colors::black())
			(stencil_op::stencil_fail = stencil_op_value::keep)
			(stencil_op::depth_fail = stencil_op_value::keep)
			(stencil_op::pass = stencil_op_value::keep)
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
