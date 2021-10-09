//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/d3d9/d3dinclude.hpp>
#include <sge/d3d9/state/convert/light/cutoff_angle.hpp>
#include <sge/renderer/state/ffp/lighting/light/cutoff_angle.hpp>

void sge::d3d9::state::convert::light::cutoff_angle(
    D3DLIGHT9 &_light, sge::renderer::state::ffp::lighting::light::cutoff_angle const _angle)
{
  _light.Phi = _angle.get();

  _light.Theta = _angle.get();
}
