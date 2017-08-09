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


#include <sge/evdev/joypad/create.hpp>
#include <sge/evdev/joypad/init.hpp>
#include <sge/evdev/joypad/map.hpp>
#include <sge/evdev/joypad/object.hpp>
#include <sge/evdev/joypad/shared_ptr.hpp>
#include <sge/window/object_fwd.hpp>
#include <fcppt/algorithm/map_optional.hpp>
#include <fcppt/filesystem/directory_range.hpp>
#include <fcppt/log/object_fwd.hpp>
#include <fcppt/optional/map.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/filesystem/path.hpp>
#include <fcppt/config/external_end.hpp>


sge::evdev::joypad::map
sge::evdev::joypad::init(
	fcppt::log::object &_log,
	sge::window::object &_window,
	boost::filesystem::path const &_path
)
{
	return
		fcppt::algorithm::map_optional<
			sge::evdev::joypad::map
		>(
			fcppt::filesystem::directory_range(
				_path
			),
			[
				&_log,
				&_window
			](
				boost::filesystem::path const &_cur
			)
			{
				return
					fcppt::optional::map(
						sge::evdev::joypad::create(
							_log,
							_window,
							_cur
						),
						[](
							sge::evdev::joypad::shared_ptr const _ptr
						)
						{
							return
								sge::evdev::joypad::map::value_type{
									_ptr->posix_fd(),
									_ptr
								};
						}
					);
			}
		);
}
