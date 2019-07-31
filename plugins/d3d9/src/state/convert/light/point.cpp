//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/d3d9/d3dinclude.hpp>
#include <sge/d3d9/state/convert/light/attenuation.hpp>
#include <sge/d3d9/state/convert/light/point.hpp>
#include <sge/d3d9/state/convert/light/position.hpp>
#include <sge/renderer/state/ffp/lighting/light/point.hpp>


void
sge::d3d9::state::convert::light::point(
	D3DLIGHT9 &_light,
	sge::renderer::state::ffp::lighting::light::point const &_point
)
{
	_light.Type = D3DLIGHT_POINT;

	sge::d3d9::state::convert::light::position(
		_light,
		_point.position()
	);

	sge::d3d9::state::convert::light::attenuation(
		_light,
		_point.attenuation()
	);
}
