/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2014 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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


#include <sge/log/option.hpp>
#include <fcppt/log/level.hpp>
#include <fcppt/log/location.hpp>


sge::log::option::option(
	fcppt::log::location const &_location,
	fcppt::log::level const _level
)
:
	location_(
		_location
	),
	level_(
		_level
	)
{
}

fcppt::log::location const &
sge::log::option::location() const
{
	return
		location_;
}

fcppt::log::level
sge::log::option::level() const
{
	return
		level_;
}
