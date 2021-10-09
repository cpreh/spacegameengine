//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/d3d9/d3dinclude.hpp>
#include <sge/d3d9/optional_lock_box.hpp>
#include <sge/d3d9/convert/lock_box.hpp>
#include <sge/d3d9/volumefuncs/lock_box.hpp>
#include <sge/renderer/exception.hpp>
#include <sge/renderer/lock_box_fwd.hpp>
#include <fcppt/text.hpp>
#include <fcppt/optional/maybe_void.hpp>

D3DLOCKED_BOX const sge::d3d9::volumefuncs::lock_box(
    IDirect3DVolume9 &_volume,
    sge::d3d9::optional_lock_box const &_opt_box,
    sge::d3d9::lock_flags const _flags)
{
  D3DLOCKED_BOX ret;

  D3DBOX in_box;

  fcppt::optional::maybe_void(
      _opt_box,
      [&in_box](sge::renderer::lock_box const &_box)
      { in_box = sge::d3d9::convert::lock_box(_box); });

  if (_volume.LockBox(&ret, _opt_box.has_value() ? &in_box : nullptr, _flags.get()) != D3D_OK)
    throw sge::renderer::exception{FCPPT_TEXT("Volume::LockBox() failed!")};

  return ret;
}
