//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_RENDERER_STATE_CORE_DEPTH_STENCIL_DEPTH_FUNC_HPP_INCLUDED
#define SGE_RENDERER_STATE_CORE_DEPTH_STENCIL_DEPTH_FUNC_HPP_INCLUDED

#include <sge/renderer/state/core/depth_stencil/depth/func_fwd.hpp> // IWYU pragma: keep

namespace sge::renderer::state::core::depth_stencil::depth
{

enum class func
{
  never,
  less,
  equal,
  less_equal,
  greater,
  not_equal,
  greater_equal,
  always
};

}

#endif
