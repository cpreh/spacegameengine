/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2016 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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


#include <sge/evdev/joypad/add.hpp>
#include <sge/evdev/joypad/add_parameters_fwd.hpp>
#include <sge/evdev/joypad/init.hpp>
#include <fcppt/filesystem/directory_range.hpp>
#include <fcppt/log/object_fwd.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/algorithm/string/predicate.hpp>
#include <boost/filesystem/path.hpp>
#include <fcppt/config/external_end.hpp>


void
sge::evdev::joypad::init(
	fcppt::log::object &_log,
	sge::evdev::joypad::add_parameters const &_parameters,
	boost::filesystem::path const &_path
)
{
	for(
		boost::filesystem::path const &cur
		:
		fcppt::filesystem::directory_range(
			_path
		)
	)
	{
		if(
			boost::filesystem::is_directory(
				cur
			)
		)
			continue;

		if(
			!boost::algorithm::starts_with(
				cur.filename().string(),
				"event"
			)
		)
			continue;

		sge::evdev::joypad::add(
			_log,
			_parameters,
			cur
		);
	}
}
