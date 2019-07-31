//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/d3d9/d3dinclude.hpp>
#include <sge/d3d9/state/convert/light/direction.hpp>
#include <sge/d3d9/state/convert/light/directional.hpp>
#include <sge/renderer/state/ffp/lighting/light/directional.hpp>


void
sge::d3d9::state::convert::light::directional(
	D3DLIGHT9 &_light,
	sge::renderer::state::ffp::lighting::light::directional const &_directional
)
{
	_light.Type = D3DLIGHT_DIRECTIONAL;

	sge::d3d9::state::convert::light::direction(
		_light,
		_directional.direction()
	);
}
