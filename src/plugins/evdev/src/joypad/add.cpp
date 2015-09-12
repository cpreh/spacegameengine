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


#include <sge/evdev/device/create_fd.hpp>
#include <sge/evdev/device/fd.hpp>
#include <sge/evdev/device/fd_unique_ptr.hpp>
#include <sge/evdev/joypad/add.hpp>
#include <sge/evdev/joypad/add_parameters.hpp>
#include <sge/evdev/joypad/info.hpp>
#include <sge/evdev/joypad/is_joypad.hpp>
#include <sge/evdev/joypad/make_info.hpp>
#include <sge/evdev/joypad/object.hpp>
#include <sge/input/joypad/discover_event.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/maybe_void.hpp>
#include <fcppt/assert/error.hpp>
#include <fcppt/signal/object_impl.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/filesystem/path.hpp>
#include <functional>
#include <fcppt/config/external_end.hpp>


void
sge::evdev::joypad::add(
	sge::evdev::joypad::add_parameters const &_parameters,
	boost::filesystem::path const &_path
)
{
	fcppt::maybe_void(
		sge::evdev::device::create_fd(
			_path
		),
		[
			&_parameters,
			&_path
		](
			sge::evdev::device::fd_unique_ptr &&_fd
		)
		{
			fcppt::maybe_void(
				sge::evdev::joypad::make_info(
					*_fd
				),
				[
					&_fd,
					&_parameters,
					&_path
				](
					sge::evdev::joypad::info const &_info
				)
				{
					if(
						!sge::evdev::joypad::is_joypad(
							_info
						)
					)
						return;

					typedef std::pair<
						sge::evdev::joypad::map::iterator,
						bool
					> insert_return;

					insert_return const ret(
						_parameters.map().emplace(
							_path,
							fcppt::make_unique_ptr<
								sge::evdev::joypad::object
							>(
								_parameters.focus_manager(),
								_parameters.processor(),
								std::move(
									_fd
								),
								_info
							)
						)
					);

					FCPPT_ASSERT_ERROR(
						ret.second
					);

					_parameters.discover_signal()(
						sge::input::joypad::discover_event(
							*ret.first->second
						)
					);
				}
			);
		}
	);
}
