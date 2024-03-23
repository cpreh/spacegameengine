//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_RENDERER_STATE_CORE_SAMPLER_ADDRESS_MODE_HPP_INCLUDED
#define SGE_RENDERER_STATE_CORE_SAMPLER_ADDRESS_MODE_HPP_INCLUDED

#include <sge/renderer/state/core/sampler/address/mode_fwd.hpp> // IWYU pragma: keep
#include <fcppt/config/external_begin.hpp>
#include <cstdint>
#include <fcppt/config/external_end.hpp>

namespace sge::renderer::state::core::sampler::address
{

enum class mode : std::uint8_t
{
  clamp,
  mirror_repeat,
  repeat
};

}

#endif
