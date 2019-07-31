//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


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
#include <fcppt/container/join.hpp>


sge::d3d9::state::core::depth_stencil::stencil::enabled_visitor::result_type
sge::d3d9::state::core::depth_stencil::stencil::enabled_visitor::operator()(
	sge::renderer::state::core::depth_stencil::stencil::combined const &_combined
) const
{
	return
		fcppt::container::join(
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
		fcppt::container::join(
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
