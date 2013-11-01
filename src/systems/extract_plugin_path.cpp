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


#include <sge/config/plugin_path.hpp>
#include <sge/src/systems/extract_config.hpp>
#include <sge/src/systems/extract_plugin_path.hpp>
#include <sge/src/systems/plugin_path.hpp>
#include <sge/systems/config.hpp>
#include <sge/systems/detail/any_map.hpp>


sge::systems::plugin_path
sge::systems::extract_plugin_path(
	sge::systems::detail::any_map const &_param
)
{
	sge::systems::config const config(
		sge::systems::extract_config(
			_param
		)
	);

	return
		sge::systems::plugin_path(
			config.plugin_path()
			?
				*config.plugin_path()
			:
				sge::config::plugin_path()
		);
}
