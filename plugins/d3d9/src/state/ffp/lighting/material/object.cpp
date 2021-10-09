//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/d3d9/d3dinclude.hpp>
#include <sge/d3d9/devicefuncs/set_material.hpp>
#include <sge/d3d9/state/ffp/lighting/material/object.hpp>
#include <sge/d3d9/state/ffp/lighting/material/state.hpp>
#include <sge/renderer/state/ffp/lighting/material/object.hpp>

sge::d3d9::state::ffp::lighting::material::object::object(
    IDirect3DDevice9 &_device, sge::d3d9::state::ffp::lighting::material::state const &_state)
    : sge::renderer::state::ffp::lighting::material::object(), device_(_device), state_(_state)
{
}

sge::d3d9::state::ffp::lighting::material::object::~object() {}

void sge::d3d9::state::ffp::lighting::material::object::set() const
{
  sge::d3d9::devicefuncs::set_material(device_, state_.material());
}
