//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/renderer/state/core/blend/alpha_dest.hpp>
#include <sge/renderer/state/core/blend/alpha_source.hpp>
#include <sge/renderer/state/core/blend/color_dest.hpp>
#include <sge/renderer/state/core/blend/color_source.hpp>
#include <sge/renderer/state/core/blend/separate.hpp>

sge::renderer::state::core::blend::separate::separate(
    sge::renderer::state::core::blend::color_source const _color_source,
    sge::renderer::state::core::blend::color_dest const _color_dest,
    sge::renderer::state::core::blend::alpha_source const _alpha_source,
    sge::renderer::state::core::blend::alpha_dest const _alpha_dest)
    : color_source_(_color_source),
      color_dest_(_color_dest),
      alpha_source_(_alpha_source),
      alpha_dest_(_alpha_dest)
{
}

sge::renderer::state::core::blend::color_source
sge::renderer::state::core::blend::separate::color_source() const
{
  return color_source_;
}

sge::renderer::state::core::blend::color_dest
sge::renderer::state::core::blend::separate::color_dest() const
{
  return color_dest_;
}

sge::renderer::state::core::blend::alpha_source
sge::renderer::state::core::blend::separate::alpha_source() const
{
  return alpha_source_;
}

sge::renderer::state::core::blend::alpha_dest
sge::renderer::state::core::blend::separate::alpha_dest() const
{
  return alpha_dest_;
}
