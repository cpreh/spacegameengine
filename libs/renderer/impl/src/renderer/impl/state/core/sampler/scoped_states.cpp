//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/renderer/impl/state/core/sampler/scoped_states.hpp>
#include <sge/renderer/state/core/sampler/const_object_ref_map.hpp>
#include <sge/renderer/state/core/sampler/const_optional_object_ref.hpp>
#include <sge/renderer/state/core/sampler/const_optional_object_ref_map.hpp>
#include <fcppt/algorithm/map.hpp>
#include <fcppt/config/external_begin.hpp>
#include <utility>
#include <fcppt/config/external_end.hpp>

sge::renderer::state::core::sampler::const_optional_object_ref_map
sge::renderer::impl::state::core::sampler::scoped_states(
    sge::renderer::state::core::sampler::const_object_ref_map const &_map)
{
  return fcppt::algorithm::map<sge::renderer::state::core::sampler::const_optional_object_ref_map>(
      _map,
      [](sge::renderer::state::core::sampler::const_object_ref_map::value_type const &_element)
      {
        return std::make_pair(
            _element.first,
            sge::renderer::state::core::sampler::const_optional_object_ref(_element.second));
      });
}
