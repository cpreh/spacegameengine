//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_RENDERER_STATE_CORE_DEPTH_STENCIL_STENCIL_FUNC_HPP_INCLUDED
#define SGE_RENDERER_STATE_CORE_DEPTH_STENCIL_STENCIL_FUNC_HPP_INCLUDED

#include <sge/renderer/state/core/depth_stencil/stencil/func_fwd.hpp> // IWYU pragma: keep
#include <fcppt/config/external_begin.hpp>
#include <cstdint>
#include <fcppt/config/external_end.hpp>

namespace sge::renderer::state::core::depth_stencil::stencil
{

enum class func : std::uint8_t
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
