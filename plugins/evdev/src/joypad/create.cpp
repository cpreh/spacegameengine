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
#include <sge/evdev/joypad/create.hpp>
#include <sge/evdev/joypad/info.hpp>
#include <sge/evdev/joypad/is_joypad.hpp>
#include <sge/evdev/joypad/make_info.hpp>
#include <sge/evdev/joypad/object.hpp>
#include <sge/evdev/joypad/optional_shared_ptr.hpp>
#include <sge/evdev/joypad/shared_ptr.hpp>
#include <sge/input/exception.hpp>
#include <sge/window/object_fwd.hpp>
#include <fcppt/make_shared_ptr.hpp>
#include <fcppt/text.hpp>
#include <fcppt/filesystem/path_to_string.hpp>
#include <fcppt/log/out.hpp>
#include <fcppt/log/error.hpp>
#include <fcppt/log/object_fwd.hpp>
#include <fcppt/optional/bind.hpp>
#include <fcppt/optional/join.hpp>
#include <fcppt/optional/make_if.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/filesystem/operations.hpp>
#include <boost/filesystem/path.hpp>
#include <boost/algorithm/string/predicate.hpp>
#include <utility>
#include <fcppt/config/external_end.hpp>


namespace
{

sge::evdev::joypad::optional_shared_ptr
try_create(
	fcppt::log::object &_log,
	sge::window::object &_window,
	boost::filesystem::path const &_path
)
{
	return
		fcppt::optional::bind(
			sge::evdev::device::create_fd(
				_log,
				_path
			),
			[
				&_log,
				&_window,
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

					return
						fcppt::optional::make_if(
							sge::evdev::joypad::is_joypad(
								info
							),
							[
								&info,
								&_path,
								&_window,
								&_fd
							]{
								return
									sge::evdev::joypad::shared_ptr{
										fcppt::make_shared_ptr<
											sge::evdev::joypad::object
										>(
											std::move(
												_fd
											),
											_path,
											_window,
											info
										)
									};
							}
						);
				}
				catch(
					sge::input::exception const &_exception
				)
				{
					FCPPT_LOG_ERROR(
						_log,
						fcppt::log::out
							<<
							fcppt::filesystem::path_to_string(
								_path
							)
							<<
							FCPPT_TEXT(": ")
							<<
							_exception.string()
					);

					return
						sge::evdev::joypad::optional_shared_ptr{};
				}
			}
		);
}

}

sge::evdev::joypad::optional_shared_ptr
sge::evdev::joypad::create(
	fcppt::log::object &_log,
	sge::window::object &_window,
	boost::filesystem::path const &_path
)
{
	return
		fcppt::optional::join(
			fcppt::optional::make_if(
				boost::filesystem::is_directory(
					_path
				)
				&&
				boost::algorithm::starts_with(
					_path.filename().string(),
					"event"
				),
				[
					&_log,
					&_window,
					&_path
				]{
					return
						try_create(
							_log,
							_window,
							_path
						);
				}
			)
		);
}
