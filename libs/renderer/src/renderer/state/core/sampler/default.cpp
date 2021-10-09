//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/renderer/state/core/sampler/default.hpp>
#include <sge/renderer/state/core/sampler/parameters.hpp>
#include <sge/renderer/state/core/sampler/address/default.hpp>
#include <sge/renderer/state/core/sampler/filter/default.hpp>

sge::renderer::state::core::sampler::parameters sge::renderer::state::core::sampler::default_()
{
  return sge::renderer::state::core::sampler::parameters(
      sge::renderer::state::core::sampler::address::default_(),
      sge::renderer::state::core::sampler::filter::default_());
}
