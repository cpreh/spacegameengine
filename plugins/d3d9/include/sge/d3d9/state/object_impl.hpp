//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_D3D9_STATE_OBJECT_IMPL_HPP_INCLUDED
#define SGE_D3D9_STATE_OBJECT_IMPL_HPP_INCLUDED

#include <sge/d3d9/d3dinclude.hpp>
#include <sge/d3d9/devicefuncs/set_render_state.hpp>
#include <sge/d3d9/state/object.hpp>
#include <sge/d3d9/state/render_vector.hpp>

template <typename State>
sge::d3d9::state::object<State>::object(
    IDirect3DDevice9 &_device, sge::d3d9::state::render_vector const &_states)
    : device_(_device), states_(_states)
{
}

template <typename State>
sge::d3d9::state::object<State>::~object()
{
}

template <typename State>
void sge::d3d9::state::object<State>::set() const
{
  for (sge::d3d9::state::render_vector::const_iterator it(states_.begin()); it != states_.end();
       ++it)
    sge::d3d9::devicefuncs::set_render_state(device_, it->state(), it->value());
}

#endif
