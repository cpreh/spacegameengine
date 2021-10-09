//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/renderer/state/core/sampler/address/mode.hpp>
#include <sge/renderer/state/core/sampler/address/mode_default.hpp>

sge::renderer::state::core::sampler::address::mode
sge::renderer::state::core::sampler::address::mode_default()
{
  return sge::renderer::state::core::sampler::address::mode::repeat;
}
