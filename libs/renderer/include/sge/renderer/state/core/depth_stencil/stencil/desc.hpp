//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_RENDERER_STATE_CORE_DEPTH_STENCIL_STENCIL_DESC_HPP_INCLUDED
#define SGE_RENDERER_STATE_CORE_DEPTH_STENCIL_STENCIL_DESC_HPP_INCLUDED

#include <sge/renderer/detail/symbol.hpp>
#include <sge/renderer/state/core/depth_stencil/stencil/depth_fail_op.hpp>
#include <sge/renderer/state/core/depth_stencil/stencil/desc_fwd.hpp>
#include <sge/renderer/state/core/depth_stencil/stencil/fail_op.hpp>
#include <sge/renderer/state/core/depth_stencil/stencil/func.hpp>
#include <sge/renderer/state/core/depth_stencil/stencil/pass_op.hpp>

namespace sge::renderer::state::core::depth_stencil::stencil
{

class desc
{
public:
  SGE_RENDERER_DETAIL_SYMBOL
  desc(
      sge::renderer::state::core::depth_stencil::stencil::fail_op,
      sge::renderer::state::core::depth_stencil::stencil::depth_fail_op,
      sge::renderer::state::core::depth_stencil::stencil::pass_op,
      sge::renderer::state::core::depth_stencil::stencil::func);

  [[nodiscard]] SGE_RENDERER_DETAIL_SYMBOL
      sge::renderer::state::core::depth_stencil::stencil::fail_op
      fail_op() const;

  [[nodiscard]] SGE_RENDERER_DETAIL_SYMBOL
      sge::renderer::state::core::depth_stencil::stencil::depth_fail_op
      depth_fail_op() const;

  [[nodiscard]] SGE_RENDERER_DETAIL_SYMBOL
      sge::renderer::state::core::depth_stencil::stencil::pass_op
      pass_op() const;

  [[nodiscard]] SGE_RENDERER_DETAIL_SYMBOL sge::renderer::state::core::depth_stencil::stencil::func
  func() const;

private:
  sge::renderer::state::core::depth_stencil::stencil::fail_op fail_op_;

  sge::renderer::state::core::depth_stencil::stencil::depth_fail_op depth_fail_op_;

  sge::renderer::state::core::depth_stencil::stencil::pass_op pass_op_;

  sge::renderer::state::core::depth_stencil::stencil::func func_;
};

}

#endif
