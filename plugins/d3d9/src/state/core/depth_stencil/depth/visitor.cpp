//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/d3d9/d3dinclude.hpp>
#include <sge/d3d9/state/render.hpp>
#include <sge/d3d9/state/render_vector.hpp>
#include <sge/d3d9/state/convert/bool_to_dword.hpp>
#include <sge/d3d9/state/convert/depth_func.hpp>
#include <sge/d3d9/state/core/depth_stencil/depth/visitor.hpp>
#include <sge/renderer/state/core/depth_stencil/depth/enabled.hpp>
#include <sge/renderer/state/core/depth_stencil/depth/off_fwd.hpp>


sge::d3d9::state::core::depth_stencil::depth::visitor::result_type
sge::d3d9::state::core::depth_stencil::depth::visitor::operator()(
	sge::renderer::state::core::depth_stencil::depth::off const &
) const
{
	return
		sge::d3d9::state::render_vector{
			sge::d3d9::state::render(
				D3DRS_ZENABLE,
				D3DZB_FALSE
			)
		};
}

sge::d3d9::state::core::depth_stencil::depth::visitor::result_type
sge::d3d9::state::core::depth_stencil::depth::visitor::operator()(
	sge::renderer::state::core::depth_stencil::depth::enabled const &_enabled
) const
{
	return
		sge::d3d9::state::render_vector{
			sge::d3d9::state::render(
				D3DRS_ZENABLE,
				D3DZB_TRUE
			),
			sge::d3d9::state::render(
				D3DRS_ZFUNC,
				sge::d3d9::state::convert::depth_func(
					_enabled.func()
				)
			),
			sge::d3d9::state::render(
				D3DRS_ZWRITEENABLE,
				sge::d3d9::state::convert::bool_to_dword(
					_enabled.write_enable().get()
				)
			)
		};
}
