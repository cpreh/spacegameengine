//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_RENDERER_STATE_CORE_DEPTH_STENCIL_DEPTH_ENABLED_HPP_INCLUDED
#define SGE_RENDERER_STATE_CORE_DEPTH_STENCIL_DEPTH_ENABLED_HPP_INCLUDED

#include <sge/renderer/detail/symbol.hpp>
#include <sge/renderer/state/core/depth_stencil/depth/enabled_fwd.hpp> // IWYU pragma: keep
#include <sge/renderer/state/core/depth_stencil/depth/func.hpp>
#include <sge/renderer/state/core/depth_stencil/depth/write_enable.hpp>

namespace sge::renderer::state::core::depth_stencil::depth
{

class enabled
{
public:
  SGE_RENDERER_DETAIL_SYMBOL
  enabled(
      sge::renderer::state::core::depth_stencil::depth::func,
      sge::renderer::state::core::depth_stencil::depth::write_enable);

  [[nodiscard]] SGE_RENDERER_DETAIL_SYMBOL sge::renderer::state::core::depth_stencil::depth::func
  func() const;

  [[nodiscard]] SGE_RENDERER_DETAIL_SYMBOL
      sge::renderer::state::core::depth_stencil::depth::write_enable
      write_enable() const;

private:
  sge::renderer::state::core::depth_stencil::depth::func func_;

  sge::renderer::state::core::depth_stencil::depth::write_enable write_enable_;
};

}

#endif
