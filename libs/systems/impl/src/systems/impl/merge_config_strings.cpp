//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/parse/ini/entry_name.hpp>
#include <sge/parse/ini/find_value.hpp>
#include <sge/parse/ini/optional_start_fwd.hpp>
#include <sge/parse/ini/start_fwd.hpp>
#include <sge/parse/ini/value.hpp>
#include <sge/plugin/name.hpp>
#include <sge/systems/optional_name.hpp>
#include <sge/systems/impl/ini_section_name.hpp>
#include <sge/systems/impl/merge_config_strings.hpp>
#include <fcppt/from_std_string.hpp>
#include <fcppt/optional/bind.hpp>
#include <fcppt/optional/map.hpp>


sge::systems::optional_name
sge::systems::impl::merge_config_strings(
	sge::systems::optional_name const &_parameter_name,
	sge::parse::ini::optional_start const &_ini_config,
	sge::parse::ini::entry_name const &_entry_name
)
{
	return
		_parameter_name.has_value()
		?
			_parameter_name
		:
			fcppt::optional::map(
				fcppt::optional::bind(
					_ini_config,
					[
						&_entry_name
					](
						sge::parse::ini::start const &_start
					)
					{
						return
							sge::parse::ini::find_value(
								_start,
								sge::systems::impl::ini_section_name(),
								_entry_name
							);
					}
				),
				[](
					sge::parse::ini::value const &_ini_value
				)
				{
					return
						sge::plugin::name(
							fcppt::from_std_string(
								_ini_value.get()
							)
						);
				}
			)
		;
}
