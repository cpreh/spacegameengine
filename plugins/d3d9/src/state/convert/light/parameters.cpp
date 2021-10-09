//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/d3d9/d3dinclude.hpp>
#include <sge/d3d9/convert/to_color_value.hpp>
#include <sge/d3d9/state/convert/light/parameters.hpp>
#include <sge/d3d9/state/convert/light/visitor.hpp>
#include <sge/renderer/state/ffp/lighting/light/parameters.hpp>
#include <fcppt/variant/apply.hpp>
#include <fcppt/config/external_begin.hpp>
#include <cfloat>
#include <cmath>
#include <fcppt/config/external_end.hpp>

D3DLIGHT9 const sge::d3d9::state::convert::light::parameters(
    sge::renderer::state::ffp::lighting::light::parameters const &_light)
{
  D3DLIGHT9 ret;

  fcppt::variant::apply(sge::d3d9::state::convert::light::visitor(ret), _light.variant());

  ret.Diffuse = sge::d3d9::convert::to_color_value(_light.diffuse().get());

  ret.Specular = sge::d3d9::convert::to_color_value(_light.specular().get());

  ret.Ambient = sge::d3d9::convert::to_color_value(_light.ambient().get());

  ret.Range = std::sqrt(FLT_MAX);

  ret.Falloff = 1.0f;

  return ret;
}
