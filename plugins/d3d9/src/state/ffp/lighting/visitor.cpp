//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/d3d9/d3dinclude.hpp>
#include <sge/d3d9/convert/to_color.hpp>
#include <sge/d3d9/state/render.hpp>
#include <sge/d3d9/state/render_vector.hpp>
#include <sge/d3d9/state/ffp/lighting/visitor.hpp>
#include <sge/renderer/state/ffp/lighting/enabled.hpp>
#include <sge/renderer/state/ffp/lighting/off_fwd.hpp>


sge::d3d9::state::ffp::lighting::visitor::result_type
sge::d3d9::state::ffp::lighting::visitor::operator()(
	sge::renderer::state::ffp::lighting::off const &
) const
{
	return
		sge::d3d9::state::render_vector{
			sge::d3d9::state::render(
				D3DRS_LIGHTING,
				FALSE
			)
		};
}

sge::d3d9::state::ffp::lighting::visitor::result_type
sge::d3d9::state::ffp::lighting::visitor::operator()(
	sge::renderer::state::ffp::lighting::enabled const &_enabled
) const
{
	return
		sge::d3d9::state::render_vector{
			sge::d3d9::state::render(
				D3DRS_LIGHTING,
				TRUE
			),
			sge::d3d9::state::render(
				D3DRS_AMBIENT,
				sge::d3d9::convert::to_color(
					_enabled.ambient_color().get()
				)
			),
			sge::d3d9::state::render(
				D3DRS_COLORVERTEX,
				_enabled.diffuse_from_vertex().get()
			)
		};
}
