//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/systems/config.hpp>
#include <sge/systems/exception.hpp>
#include <sge/systems/detail/any.hpp>
#include <sge/systems/detail/any_key.hpp>
#include <sge/systems/detail/any_map.hpp>
#include <sge/systems/impl/extract_config.hpp>
#include <fcppt/reference_impl.hpp>
#include <fcppt/text.hpp>
#include <fcppt/container/find_opt_mapped.hpp>
#include <fcppt/optional/maybe.hpp>
#include <fcppt/optional/to_exception.hpp>
#include <fcppt/variant/to_optional.hpp>

sge::systems::config sge::systems::impl::extract_config(sge::systems::detail::any_map const &_map)
{
  return fcppt::optional::maybe(
      fcppt::container::find_opt_mapped(_map, sge::systems::detail::any_key::config),
      [] { return sge::systems::config(); },
      [](fcppt::reference<sge::systems::detail::any const> const _config)
      {
        return fcppt::optional::to_exception(
            fcppt::variant::to_optional<sge::systems::config>(_config.get()),
            [] { return sge::systems::exception{FCPPT_TEXT("Invalid config element!")}; });
      });
}
