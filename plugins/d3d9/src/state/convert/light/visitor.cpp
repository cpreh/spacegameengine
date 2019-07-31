//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/d3d9/d3dinclude.hpp>
#include <sge/d3d9/state/convert/light/directional.hpp>
#include <sge/d3d9/state/convert/light/point.hpp>
#include <sge/d3d9/state/convert/light/spot.hpp>
#include <sge/d3d9/state/convert/light/visitor.hpp>
#include <sge/renderer/state/ffp/lighting/light/directional_fwd.hpp>
#include <sge/renderer/state/ffp/lighting/light/point_fwd.hpp>
#include <sge/renderer/state/ffp/lighting/light/spot_fwd.hpp>


sge::d3d9::state::convert::light::visitor::visitor(
	D3DLIGHT9 &_object
)
:
	object_(
		_object
	)
{
}

sge::d3d9::state::convert::light::visitor::result_type
sge::d3d9::state::convert::light::visitor::operator()(
	sge::renderer::state::ffp::lighting::light::directional const &_directional
) const
{
	sge::d3d9::state::convert::light::directional(
		object_.get(),
		_directional
	);
}

sge::d3d9::state::convert::light::visitor::result_type
sge::d3d9::state::convert::light::visitor::operator()(
	sge::renderer::state::ffp::lighting::light::point const &_point
) const
{
	sge::d3d9::state::convert::light::point(
		object_.get(),
		_point
	);
}

sge::d3d9::state::convert::light::visitor::result_type
sge::d3d9::state::convert::light::visitor::operator()(
	sge::renderer::state::ffp::lighting::light::spot const &_spot
) const
{
	sge::d3d9::state::convert::light::spot(
		object_.get(),
		_spot
	);
}
