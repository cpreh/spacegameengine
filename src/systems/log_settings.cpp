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


#include <sge/systems/log_settings.hpp>
#include <sge/systems/optional_path.hpp>
#include <fcppt/log/level.hpp>
#include <fcppt/log/location.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/filesystem/path.hpp>
#include <fcppt/config/external_end.hpp>


sge::systems::log_settings::log_settings(
	fcppt::log::location const &_location,
	fcppt::log::level const _level
)
:
	location_(
		_location
	),
	level_(
		_level
	),
	redirect_()
{
}

sge::systems::log_settings &
sge::systems::log_settings::redirect(
	boost::filesystem::path const &_path
)
{
	redirect_ =
		_path;

	return
		*this;
}

fcppt::log::location const &
sge::systems::log_settings::location() const
{
	return
		location_;
}

fcppt::log::level
sge::systems::log_settings::level() const
{
	return
		level_;
}

sge::systems::optional_path const &
sge::systems::log_settings::redirect() const
{
	return
		redirect_;
}
