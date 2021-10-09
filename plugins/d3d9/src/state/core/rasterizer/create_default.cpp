//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/d3d9/d3dinclude.hpp>
#include <sge/d3d9/state/core/rasterizer/create_default.hpp>
#include <sge/d3d9/state/core/rasterizer/make_states.hpp>
#include <sge/d3d9/state/core/rasterizer/object.hpp>
#include <sge/d3d9/state/core/rasterizer/object_unique_ptr.hpp>
#include <sge/renderer/state/core/rasterizer/default.hpp>
#include <sge/renderer/state/core/rasterizer/parameters.hpp>
#include <fcppt/make_unique_ptr.hpp>

sge::d3d9::state::core::rasterizer::object_unique_ptr
sge::d3d9::state::core::rasterizer::create_default(IDirect3DDevice9 &_device)
{
  return fcppt::make_unique_ptr<sge::d3d9::state::core::rasterizer::object>(
      _device,
      sge::d3d9::state::core::rasterizer::make_states(
          sge::renderer::state::core::rasterizer::default_()));
}
