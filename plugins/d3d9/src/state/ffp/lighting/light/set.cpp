//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/d3d9/d3dinclude.hpp>
#include <sge/d3d9/devicefuncs/light_enable.hpp>
#include <sge/d3d9/state/ffp/lighting/light/object.hpp>
#include <sge/d3d9/state/ffp/lighting/light/set.hpp>
#include <sge/renderer/caps/light_indices.hpp>
#include <sge/renderer/state/index_count.hpp>
#include <sge/renderer/state/ffp/lighting/light/const_object_ref_vector.hpp>

void sge::d3d9::state::ffp::lighting::light::set(
    IDirect3DDevice9 &_device,
    sge::renderer::state::ffp::lighting::light::const_object_ref_vector const &_lights,
    sge::renderer::caps::light_indices const _max_lights)
{
  sge::renderer::state::index_count index(0u);

  for (sge::renderer::state::ffp::lighting::light::const_object_ref_vector::const_iterator it(
           _lights.begin());
       it != _lights.end();
       ++it, ++index)
  {
    static_cast<sge::d3d9::state::ffp::lighting::light::object const &>(it->get()).set(index);

    sge::d3d9::devicefuncs::light_enable(_device, index, true);
  }

  for (; index < _max_lights.get(); ++index)
    sge::d3d9::devicefuncs::light_enable(_device, index, false);
}
