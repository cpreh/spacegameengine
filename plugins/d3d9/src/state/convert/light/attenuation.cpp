//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/d3d9/d3dinclude.hpp>
#include <sge/d3d9/state/convert/light/attenuation.hpp>
#include <sge/renderer/state/ffp/lighting/light/attenuation.hpp>


void
sge::d3d9::state::convert::light::attenuation(
	D3DLIGHT9 &_light,
	sge::renderer::state::ffp::lighting::light::attenuation const &_attenuation
)
{
	_light.Attenuation0
		= _attenuation.constant().get();

	_light.Attenuation1
		= _attenuation.linear().get();

	_light.Attenuation2
		= _attenuation.quadratic().get();
}
