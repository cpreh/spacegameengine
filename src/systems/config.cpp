/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2015 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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


#include <sge/systems/config.hpp>
#include <sge/systems/log_settings.hpp>
#include <sge/systems/optional_log_settings.hpp>
#include <sge/systems/optional_plugin_path.hpp>
#include <sge/systems/plugin_path.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/filesystem/path.hpp>
#include <fcppt/config/external_end.hpp>


sge::systems::config::config()
:
	plugin_path_(),
	log_settings_()
{
}

sge::systems::config &
sge::systems::config::plugin_path(
	boost::filesystem::path const &_plugin_path
)
{
	plugin_path_ =
		sge::systems::optional_plugin_path(
			sge::systems::plugin_path(
				_plugin_path
			)
		);

	return
		*this;
}

sge::systems::config &
sge::systems::config::log_settings(
	sge::systems::log_settings const &_log_settings
)
{
	log_settings_ =
		sge::systems::optional_log_settings(
			_log_settings
		);

	return
		*this;
}

sge::systems::optional_plugin_path const &
sge::systems::config::plugin_path() const
{
	return
		plugin_path_;
}

sge::systems::optional_log_settings const &
sge::systems::config::log_settings() const
{
	return
		log_settings_;
}
