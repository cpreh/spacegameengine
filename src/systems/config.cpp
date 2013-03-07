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


#include <sge/systems/config.hpp>
#include <sge/systems/log_settings.hpp>
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
	plugin_path_ = _plugin_path;

	return *this;
}

sge::systems::config &
sge::systems::config::log_settings(
	sge::systems::log_settings const &_log_settings
)
{
	log_settings_ = _log_settings;

	return *this;
}

sge::systems::config::optional_path const &
sge::systems::config::plugin_path() const
{
	return plugin_path_;
}

sge::systems::config::optional_log_settings const &
sge::systems::config::log_settings() const
{
	return log_settings_;
}
