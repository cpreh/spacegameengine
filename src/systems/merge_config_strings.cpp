/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2013 Carl Philipp Reh (sefi@s-e-f-i.de)

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU Lesser General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
*/


#include <sge/parse/ini/entry_name.hpp>
#include <sge/parse/ini/find_value.hpp>
#include <sge/parse/ini/optional_value.hpp>
#include <sge/parse/ini/start_fwd.hpp>
#include <sge/plugin/name.hpp>
#include <sge/src/systems/ini_section_name.hpp>
#include <sge/src/systems/merge_config_strings.hpp>
#include <sge/systems/optional_name.hpp>


sge::systems::optional_name
sge::systems::merge_config_strings(
	sge::systems::optional_name const &_parameter_name,
	sge::parse::ini::start const &_ini_config,
	sge::parse::ini::entry_name const &_entry_name
)
{
	if(
		_parameter_name
	)
		return
			_parameter_name;

	sge::parse::ini::optional_value const ini_value(
		sge::parse::ini::find_value(
			_ini_config,
			sge::systems::ini_section_name(),
			_entry_name
		)
	);

	return
		ini_value
		?
			sge::systems::optional_name(
				sge::plugin::name(
					ini_value->get()
				)
			)
		:
			sge::systems::optional_name()
		;
}
