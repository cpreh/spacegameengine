//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/d3d9/state/render.hpp>
#include <sge/d3d9/state/render_vector.hpp>
#include <sge/d3d9/state/convert/bool_to_dword.hpp>
#include <sge/d3d9/state/ffp/misc/make_states.hpp>
#include <sge/renderer/state/ffp/misc/parameters.hpp>


sge::d3d9::state::render_vector
sge::d3d9::state::ffp::misc::make_states(
	sge::renderer::state::ffp::misc::parameters const &_parameters
)
{
	return
		sge::d3d9::state::render_vector{
			sge::d3d9::state::render(
				D3DRS_LOCALVIEWER,
				sge::d3d9::state::convert::bool_to_dword(
					_parameters.local_viewer().get()
				)
			),
			sge::d3d9::state::render(
				D3DRS_NORMALIZENORMALS,
				sge::d3d9::state::convert::bool_to_dword(
					_parameters.normalize_normals().get()
				)
			),
			sge::d3d9::state::render(
				D3DRS_POINTSPRITEENABLE,
				sge::d3d9::state::convert::bool_to_dword(
					_parameters.enable_point_sprites().get()
				)
			)
		};
}
