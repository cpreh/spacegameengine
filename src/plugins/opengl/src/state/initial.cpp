/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2012 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#include <sge/opengl/state/initial.hpp>
#include <sge/renderer/state/bool.hpp>
#include <sge/renderer/state/dest_blend_func.hpp>
#include <sge/renderer/state/float.hpp>
#include <sge/renderer/state/int.hpp>
#include <sge/renderer/state/list.hpp>
#include <sge/renderer/state/source_blend_func.hpp>
#include <sge/renderer/state/stencil_func.hpp>
#include <sge/renderer/state/stencil_op.hpp>
#include <sge/renderer/state/stencil_op_value.hpp>
#include <sge/renderer/state/trampoline.hpp>
#include <sge/renderer/state/uint.hpp>


sge::renderer::state::list const
sge::opengl::state::initial()
{
	return
		sge::renderer::state::list
		(
			sge::renderer::state::source_blend_func::one
		)
		(
			sge::renderer::state::dest_blend_func::zero
		)
		(
			sge::renderer::state::stencil_func::off
		)
		(
			sge::renderer::state::alpha_func::off
		)
		(
			sge::renderer::state::int_::stencil_ref = 0
		)
		(
			sge::renderer::state::uint::stencil_mask = ~0u
		)
		(
			sge::renderer::state::uint::stencil_write_mask = ~0u
		)
		(
			sge::renderer::state::float_::alpha_test_ref = 0.f
		)
		(
			sge::renderer::state::bool_::write_alpha = true
		)
		(
			sge::renderer::state::bool_::write_blue = true
		)
		(
			sge::renderer::state::bool_::write_green = true
		)
		(
			sge::renderer::state::bool_::write_red = true
		)
		(
			sge::renderer::state::stencil_op::stencil_fail
				= sge::renderer::state::stencil_op_value::keep
		)
		(
			sge::renderer::state::stencil_op::depth_fail
				= sge::renderer::state::stencil_op_value::keep
		)
		(
			sge::renderer::state::stencil_op::pass
				= sge::renderer::state::stencil_op_value::keep
		);
}
