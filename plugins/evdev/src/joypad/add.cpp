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


#include <sge/evdev/device/create_fd.hpp>
#include <sge/evdev/device/fd.hpp>
#include <sge/evdev/device/fd_unique_ptr.hpp>
#include <sge/evdev/joypad/add.hpp>
#include <sge/evdev/joypad/add_parameters.hpp>
#include <sge/evdev/joypad/info.hpp>
#include <sge/evdev/joypad/is_joypad.hpp>
#include <sge/evdev/joypad/make_info.hpp>
#include <sge/evdev/joypad/object.hpp>
#include <sge/input/exception.hpp>
#include <sge/input/joypad/discover_event.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/text.hpp>
#include <fcppt/assert/error.hpp>
#include <fcppt/filesystem/path_to_string.hpp>
#include <fcppt/log/_.hpp>
#include <fcppt/log/error.hpp>
#include <fcppt/log/object_fwd.hpp>
#include <fcppt/optional/maybe_void.hpp>
#include <fcppt/signal/object_impl.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/filesystem/path.hpp>
#include <utility>
#include <fcppt/config/external_end.hpp>


void
sge::evdev::joypad::add(
	fcppt::log::object &_log,
	sge::evdev::joypad::add_parameters const &_parameters,
	boost::filesystem::path const &_path
)
{
	fcppt::optional::maybe_void(
		sge::evdev::device::create_fd(
			_log,
			_path
		),
		[
			&_log,
			&_parameters,
			&_path
		](
			sge::evdev::device::fd_unique_ptr &&_fd
		)
		{
			try
			{
				sge::evdev::joypad::info const info(
					sge::evdev::joypad::make_info(
						*_fd
					)
				);

				if(
					!sge::evdev::joypad::is_joypad(
						info
					)
				)
					return;

				typedef
				std::pair<
					sge::evdev::joypad::map::iterator,
					bool
				>
				insert_return;

				insert_return const ret(
					_parameters.map().emplace(
						_path,
						fcppt::make_unique_ptr<
							sge::evdev::joypad::object
						>(
							_parameters.processor(),
							std::move(
								_fd
							),
							info
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
			catch(
				sge::input::exception const &_exception
			)
			{
				FCPPT_LOG_ERROR(
					_log,
					fcppt::log::_
						<<
						fcppt::filesystem::path_to_string(
							_path
						)
						<<
						FCPPT_TEXT(": ")
						<<
						_exception.string()
				);
			}
		}
	);
}
