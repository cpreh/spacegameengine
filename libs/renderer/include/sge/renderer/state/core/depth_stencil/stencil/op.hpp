//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_RENDERER_STATE_CORE_DEPTH_STENCIL_STENCIL_OP_HPP_INCLUDED
#define SGE_RENDERER_STATE_CORE_DEPTH_STENCIL_STENCIL_OP_HPP_INCLUDED

#include <sge/renderer/state/core/depth_stencil/stencil/op_fwd.hpp> // IWYU pragma: keep

namespace sge::renderer::state::core::depth_stencil::stencil
{

enum class op
{
  keep,
  zero,
  replace,
  inc_sat,
  inc_wrap,
  dec_sat,
  dec_wrap,
  invert
};

}

#endif
