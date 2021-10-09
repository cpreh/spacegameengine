//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/config/plugin_path.hpp>
#include <sge/systems/plugin_path.hpp>
#include <sge/systems/detail/any_map.hpp>
#include <sge/systems/impl/extract_config.hpp>
#include <sge/systems/impl/extract_plugin_path.hpp>
#include <fcppt/optional/from.hpp>

sge::systems::plugin_path
sge::systems::impl::extract_plugin_path(sge::systems::detail::any_map const &_map)
{
  return fcppt::optional::from(
      sge::systems::impl::extract_config(_map).plugin_path(),
      [] { return sge::systems::plugin_path(sge::config::plugin_path()); });
}
