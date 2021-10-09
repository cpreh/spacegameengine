//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_RENDERER_STATE_CORE_DEPTH_STENCIL_PARAMETERS_HPP_INCLUDED
#define SGE_RENDERER_STATE_CORE_DEPTH_STENCIL_PARAMETERS_HPP_INCLUDED

#include <sge/renderer/detail/symbol.hpp>
#include <sge/renderer/state/core/depth_stencil/parameters_fwd.hpp>
#include <sge/renderer/state/core/depth_stencil/depth/variant.hpp>
#include <sge/renderer/state/core/depth_stencil/stencil/variant.hpp>

namespace sge::renderer::state::core::depth_stencil
{

class parameters
{
public:
  SGE_RENDERER_DETAIL_SYMBOL
  parameters(
      sge::renderer::state::core::depth_stencil::depth::variant const &,
      sge::renderer::state::core::depth_stencil::stencil::variant const &);

  [[nodiscard]] SGE_RENDERER_DETAIL_SYMBOL
      sge::renderer::state::core::depth_stencil::depth::variant const &
      depth_variant() const;

  [[nodiscard]] SGE_RENDERER_DETAIL_SYMBOL
      sge::renderer::state::core::depth_stencil::stencil::variant const &
      stencil_variant() const;

private:
  sge::renderer::state::core::depth_stencil::depth::variant depth_variant_;

  sge::renderer::state::core::depth_stencil::stencil::variant stencil_variant_;
};

}

#endif
