//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/d3d9/d3dinclude.hpp>
#include <sge/d3d9/convert/vector3.hpp>
#include <sge/d3d9/state/convert/light/position.hpp>
#include <sge/renderer/state/ffp/lighting/light/position.hpp>


void
sge::d3d9::state::convert::light::position(
	D3DLIGHT9 &_light,
	sge::renderer::state::ffp::lighting::light::position const &_position
)
{
	_light.Position
		= sge::d3d9::convert::vector3(
			_position.get()
		);
}
