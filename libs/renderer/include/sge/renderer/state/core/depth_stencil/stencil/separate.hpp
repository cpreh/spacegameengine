//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_RENDERER_STATE_CORE_DEPTH_STENCIL_STENCIL_SEPARATE_HPP_INCLUDED
#define SGE_RENDERER_STATE_CORE_DEPTH_STENCIL_STENCIL_SEPARATE_HPP_INCLUDED

#include <sge/renderer/detail/symbol.hpp>
#include <sge/renderer/state/core/depth_stencil/stencil/back.hpp>
#include <sge/renderer/state/core/depth_stencil/stencil/front.hpp>
#include <sge/renderer/state/core/depth_stencil/stencil/separate_fwd.hpp> // IWYU pragma: keep

namespace sge::renderer::state::core::depth_stencil::stencil
{

class separate
{
public:
  SGE_RENDERER_DETAIL_SYMBOL
  separate(
      sge::renderer::state::core::depth_stencil::stencil::front const &,
      sge::renderer::state::core::depth_stencil::stencil::back const &);

  [[nodiscard]] SGE_RENDERER_DETAIL_SYMBOL
      sge::renderer::state::core::depth_stencil::stencil::front const &
      front() const;

  [[nodiscard]] SGE_RENDERER_DETAIL_SYMBOL
      sge::renderer::state::core::depth_stencil::stencil::back const &
      back() const;

private:
  sge::renderer::state::core::depth_stencil::stencil::front front_;

  sge::renderer::state::core::depth_stencil::stencil::back back_;
};

}

#endif
