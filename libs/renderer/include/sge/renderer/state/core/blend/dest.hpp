//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_RENDERER_STATE_CORE_BLEND_DEST_HPP_INCLUDED
#define SGE_RENDERER_STATE_CORE_BLEND_DEST_HPP_INCLUDED

#include <sge/renderer/state/core/blend/dest_fwd.hpp> // IWYU pragma: keep
#include <fcppt/config/external_begin.hpp>
#include <cstdint>
#include <fcppt/config/external_end.hpp>

namespace sge::renderer::state::core::blend
{

enum class dest : std::uint8_t
{
  zero,
  one,
  src_color,
  inv_src_color,
  src_alpha,
  inv_src_alpha,
  dest_alpha,
  inv_dest_alpha
};

}

#endif
