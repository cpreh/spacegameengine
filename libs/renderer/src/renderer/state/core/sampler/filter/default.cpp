//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/renderer/state/core/sampler/filter/default.hpp>
#include <sge/renderer/state/core/sampler/filter/linear.hpp>
#include <sge/renderer/state/core/sampler/filter/parameters.hpp>

sge::renderer::state::core::sampler::filter::parameters
sge::renderer::state::core::sampler::filter::default_()
{
  return sge::renderer::state::core::sampler::filter::linear();
}
