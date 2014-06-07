/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2014 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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


#include <sge/d3d9/d3dinclude.hpp>
#include <sge/d3d9/state/render.hpp>
#include <sge/d3d9/state/render_vector.hpp>
#include <sge/d3d9/state/core/depth_stencil/stencil/enabled_visitor.hpp>
#include <sge/d3d9/state/core/depth_stencil/stencil/visitor.hpp>
#include <sge/renderer/state/core/depth_stencil/stencil/enabled.hpp>
#include <sge/renderer/state/core/depth_stencil/stencil/off_fwd.hpp>
#include <fcppt/algorithm/join.hpp>
#include <fcppt/variant/apply_unary.hpp>


sge::d3d9::state::core::depth_stencil::stencil::visitor::result_type const
sge::d3d9::state::core::depth_stencil::stencil::visitor::operator()(
	sge::renderer::state::core::depth_stencil::stencil::off const &
) const
{
	return
		sge::d3d9::state::render_vector{
			sge::d3d9::state::render(
				D3DRS_STENCILENABLE,
				FALSE
			)
		};
}

sge::d3d9::state::core::depth_stencil::stencil::visitor::result_type const
sge::d3d9::state::core::depth_stencil::stencil::visitor::operator()(
	sge::renderer::state::core::depth_stencil::stencil::enabled const &_enabled
) const
{
	return
		fcppt::algorithm::join(
			sge::d3d9::state::render_vector{
				sge::d3d9::state::render(
					D3DRS_STENCILENABLE,
					TRUE
				),
				sge::d3d9::state::render(
					D3DRS_STENCILREF,
					_enabled.ref().get()
				),
				sge::d3d9::state::render(
					D3DRS_STENCILMASK,
					_enabled.read_mask().get()
				),
				sge::d3d9::state::render(
					D3DRS_STENCILWRITEMASK,
					_enabled.write_mask().get()
				)
			},
			fcppt::variant::apply_unary(
				sge::d3d9::state::core::depth_stencil::stencil::enabled_visitor(),
				_enabled.enabled_variant()
			)
		);
}
