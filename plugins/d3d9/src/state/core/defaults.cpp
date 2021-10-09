//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/d3d9/d3dinclude.hpp>
#include <sge/d3d9/state/core/defaults.hpp>
#include <sge/d3d9/state/core/blend/create_default.hpp>
#include <sge/d3d9/state/core/blend/object.hpp>
#include <sge/d3d9/state/core/depth_stencil/create_default.hpp>
#include <sge/d3d9/state/core/depth_stencil/object.hpp>
#include <sge/d3d9/state/core/rasterizer/create_default.hpp>
#include <sge/d3d9/state/core/rasterizer/object.hpp>
#include <sge/d3d9/state/core/sampler/create_default.hpp>
#include <sge/d3d9/state/core/sampler/object.hpp>

sge::d3d9::state::core::defaults::defaults(IDirect3DDevice9 &_device)
    : blend_(sge::d3d9::state::core::blend::create_default(_device)),
      depth_stencil_(sge::d3d9::state::core::depth_stencil::create_default(_device)),
      rasterizer_(sge::d3d9::state::core::rasterizer::create_default(_device)),
      sampler_(sge::d3d9::state::core::sampler::create_default(_device))
{
}

sge::d3d9::state::core::defaults::~defaults() {}

sge::d3d9::state::core::blend::object const &sge::d3d9::state::core::defaults::blend() const
{
  return *blend_;
}

sge::d3d9::state::core::depth_stencil::object const &
sge::d3d9::state::core::defaults::depth_stencil() const
{
  return *depth_stencil_;
}

sge::d3d9::state::core::rasterizer::object const &
sge::d3d9::state::core::defaults::rasterizer() const
{
  return *rasterizer_;
}

sge::d3d9::state::core::sampler::object const &sge::d3d9::state::core::defaults::sampler() const
{
  return *sampler_;
}
