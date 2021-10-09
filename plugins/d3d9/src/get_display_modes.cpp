//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/d3d9/d3dinclude.hpp>
#include <sge/d3d9/device_index.hpp>
#include <sge/d3d9/get_display_modes.hpp>
#include <sge/d3d9/optional_display_mode.hpp>
#include <sge/d3d9/convert/to_display_mode.hpp>
#include <sge/d3d9/systemfuncs/enum_adapter_modes.hpp>
#include <sge/renderer/display_mode/container.hpp>
#include <fcppt/make_int_range_count.hpp>
#include <fcppt/algorithm/map_optional.hpp>
#include <fcppt/optional/map.hpp>

sge::renderer::display_mode::container sge::d3d9::get_display_modes(
    IDirect3D9 &_d3d9, sge::d3d9::device_index const _index, D3DFORMAT const _format)
{
  return fcppt::algorithm::map_optional<sge::renderer::display_mode::container>(
      fcppt::make_int_range_count(_d3d9.GetAdapterModeCount(_index.get(), _format)),
      [&_d3d9, _index, _format](UINT const _mode_index)
      {
        return fcppt::optional::map(
            sge::d3d9::systemfuncs::enum_adapter_modes(_d3d9, _index, _format, _mode_index),
            [](D3DDISPLAYMODE const _mode) { return sge::d3d9::convert::to_display_mode(_mode); });
      });
}
