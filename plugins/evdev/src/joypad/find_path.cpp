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


#include <sge/evdev/joypad/find_path.hpp>
#include <sge/evdev/joypad/map.hpp>
#include <sge/evdev/joypad/object.hpp>
#include <sge/evdev/joypad/optional_iterator.hpp>
#include <fcppt/const.hpp>
#include <fcppt/optional/make_if.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/filesystem/path.hpp>
#include <algorithm>
#include <fcppt/config/external_end.hpp>


sge::evdev::joypad::optional_iterator
sge::evdev::joypad::find_path(
	sge::evdev::joypad::map &_map,
	boost::filesystem::path const &_path
)
{
	// TODO: Make an algorithm for this
	sge::evdev::joypad::map::iterator const pos{
		std::find_if(
			_map.begin(),
			_map.end(),
			[
				&_path
			](
				sge::evdev::joypad::map::value_type const &_value
			)
			{
				return
					_value.second->path()
					==
					_path;
			}
		)
	};

	return
		fcppt::optional::make_if(
			pos
			!=
			_map.end(),
			fcppt::const_(
				pos
			)
		);
}
