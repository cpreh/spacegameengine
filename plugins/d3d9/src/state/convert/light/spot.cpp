//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/d3d9/d3dinclude.hpp>
#include <sge/d3d9/state/convert/light/attenuation.hpp>
#include <sge/d3d9/state/convert/light/cutoff_angle.hpp>
#include <sge/d3d9/state/convert/light/direction.hpp>
#include <sge/d3d9/state/convert/light/position.hpp>
#include <sge/d3d9/state/convert/light/spot.hpp>
#include <sge/renderer/state/ffp/lighting/light/spot.hpp>

void sge::d3d9::state::convert::light::spot(
    D3DLIGHT9 &_light, sge::renderer::state::ffp::lighting::light::spot const &_spot)
{
  _light.Type = D3DLIGHT_SPOT;

  sge::d3d9::state::convert::light::attenuation(_light, _spot.attenuation());

  sge::d3d9::state::convert::light::cutoff_angle(_light, _spot.cutoff_angle());

  sge::d3d9::state::convert::light::direction(_light, _spot.direction());

  sge::d3d9::state::convert::light::position(_light, _spot.position());
}
