//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/d3d9/d3dinclude.hpp>
#include <sge/d3d9/state/render.hpp>
#include <sge/d3d9/state/core/blend/write_mask.hpp>
#include <sge/renderer/state/core/blend/write_mask.hpp>

namespace
{

DWORD
make_flag(bool, DWORD);

}

sge::d3d9::state::render const sge::d3d9::state::core::blend::write_mask(
    sge::renderer::state::core::blend::write_mask const &_write_mask)
{
  return sge::d3d9::state::render(
      D3DRS_COLORWRITEENABLE,
      make_flag(_write_mask.write_alpha().get(), D3DCOLORWRITEENABLE_ALPHA) |
          make_flag(_write_mask.write_red().get(), D3DCOLORWRITEENABLE_RED) |
          make_flag(_write_mask.write_green().get(), D3DCOLORWRITEENABLE_GREEN) |
          make_flag(_write_mask.write_blue().get(), D3DCOLORWRITEENABLE_BLUE));
}

namespace
{

DWORD
make_flag(bool const _enabled, DWORD const _flag) { return _enabled ? _flag : 0u; }

}
