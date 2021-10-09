//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/d3d9/d3dinclude.hpp>
#include <sge/d3d9/devicefuncs/set_render_state.hpp>
#include <sge/d3d9/state/ffp/clip_plane/object.hpp>
#include <sge/d3d9/state/ffp/clip_plane/set.hpp>
#include <sge/renderer/state/index_count.hpp>
#include <sge/renderer/state/ffp/clip_plane/const_object_ref_vector.hpp>
#include <fcppt/config/external_begin.hpp>
#include <iterator>
#include <fcppt/config/external_end.hpp>

void sge::d3d9::state::ffp::clip_plane::set(
    IDirect3DDevice9 &_device,
    sge::renderer::state::ffp::clip_plane::const_object_ref_vector const &_states)
{
  DWORD indices(0u);

  for (sge::renderer::state::ffp::clip_plane::const_object_ref_vector::const_iterator it(
           _states.begin());
       it != _states.end();
       ++it)
  {
    sge::renderer::state::index_count const index(
        static_cast<sge::renderer::state::index_count>(std::distance(it, _states.end())));

    static_cast<sge::d3d9::state::ffp::clip_plane::object const &>(it->get()).set(index);

    indices |= (1u << index);
  }

  sge::d3d9::devicefuncs::set_render_state(_device, D3DRS_CLIPPLANEENABLE, indices);
}
