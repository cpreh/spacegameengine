//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/d3d9/d3dinclude.hpp>
#include <sge/d3d9/state/render.hpp>
#include <sge/d3d9/state/render_vector.hpp>
#include <sge/d3d9/state/convert/bool_to_dword.hpp>
#include <sge/d3d9/state/convert/cull_mode.hpp>
#include <sge/d3d9/state/convert/fill_mode.hpp>
#include <sge/d3d9/state/core/rasterizer/make_states.hpp>
#include <sge/renderer/state/core/rasterizer/parameters.hpp>


sge::d3d9::state::render_vector
sge::d3d9::state::core::rasterizer::make_states(
	sge::renderer::state::core::rasterizer::parameters const &_parameters
)
{
	return
		sge::d3d9::state::render_vector{
			sge::d3d9::state::render(
				D3DRS_CULLMODE,
				sge::d3d9::state::convert::cull_mode(
					_parameters.cull_mode()
				)
			),
			sge::d3d9::state::render(
				D3DRS_FILLMODE,
				sge::d3d9::state::convert::fill_mode(
					_parameters.fill_mode()
				)
			),
			sge::d3d9::state::render(
				D3DRS_SCISSORTESTENABLE,
				sge::d3d9::state::convert::bool_to_dword(
					_parameters.enable_scissor_test().get()
				)
			)
		};
}
