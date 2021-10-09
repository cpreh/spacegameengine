//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/d3d9/d3dinclude.hpp>
#include <sge/d3d9/devicefuncs/set_clip_plane.hpp>
#include <sge/renderer/exception.hpp>
#include <sge/renderer/state/index_count.hpp>
#include <sge/renderer/state/ffp/clip_plane/area.hpp>
#include <fcppt/text.hpp>

void sge::d3d9::devicefuncs::set_clip_plane(
    IDirect3DDevice9 &_device,
    sge::renderer::state::index_count const _index,
    sge::renderer::state::ffp::clip_plane::area const &_value)
{
  if (_device.SetClipPlane(_index, _value.get().storage().data()) != D3D_OK)
    throw sge::renderer::exception(FCPPT_TEXT("SetClipPlane() failed!"));
}
