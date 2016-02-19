/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2016 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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
#include <sge/d3d9/state/convert/stencil_func.hpp>
#include <sge/d3d9/state/convert/stencil_op.hpp>
#include <sge/d3d9/state/core/depth_stencil/stencil/enabled_visitor.hpp>
#include <sge/d3d9/state/core/depth_stencil/stencil/one_side.hpp>
#include <sge/renderer/state/core/depth_stencil/stencil/combined.hpp>
#include <sge/renderer/state/core/depth_stencil/stencil/desc.hpp>
#include <sge/renderer/state/core/depth_stencil/stencil/separate.hpp>
#include <fcppt/algorithm/join.hpp>


sge::d3d9::state::core::depth_stencil::stencil::enabled_visitor::result_type
sge::d3d9::state::core::depth_stencil::stencil::enabled_visitor::operator()(
	sge::renderer::state::core::depth_stencil::stencil::combined const &_combined
) const
{
	return
		fcppt::algorithm::join(
			sge::d3d9::state::render_vector{
				sge::d3d9::state::render(
					D3DRS_TWOSIDEDSTENCILMODE,
					FALSE
				)
			},
			sge::d3d9::state::core::depth_stencil::stencil::one_side(
				_combined.desc()
			)
		);
}

sge::d3d9::state::core::depth_stencil::stencil::enabled_visitor::result_type
sge::d3d9::state::core::depth_stencil::stencil::enabled_visitor::operator()(
	sge::renderer::state::core::depth_stencil::stencil::separate const &_separate
) const
{
	// TODO: Is this right?
	sge::renderer::state::core::depth_stencil::stencil::desc const &ccw(
		_separate.front().get()
	);

	return
		fcppt::algorithm::join(
			sge::d3d9::state::render_vector{
				sge::d3d9::state::render(
					D3DRS_TWOSIDEDSTENCILMODE,
					TRUE
				),
				sge::d3d9::state::render(
					D3DRS_CCW_STENCILFAIL,
					sge::d3d9::state::convert::stencil_op(
						ccw.fail_op().get()
					)
				),
				sge::d3d9::state::render(
					D3DRS_CCW_STENCILZFAIL,
					sge::d3d9::state::convert::stencil_op(
						ccw.depth_fail_op().get()
					)
				),
				sge::d3d9::state::render(
					D3DRS_CCW_STENCILPASS,
					sge::d3d9::state::convert::stencil_op(
						ccw.pass_op().get()
					)
				),
				sge::d3d9::state::render(
					D3DRS_CCW_STENCILFUNC,
					sge::d3d9::state::convert::stencil_func(
						ccw.func()
					)
				)
			},
			sge::d3d9::state::core::depth_stencil::stencil::one_side(
				_separate.back().get()
			)
		);
}
