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


#include <sge/evdev/device/fd.hpp>
#include <sge/evdev/device/unique_id.hpp>
#include <sge/input/exception.hpp>
#include <sge/input/info/unique_id.hpp>
#include <fcppt/from_std_string.hpp>
#include <fcppt/text.hpp>
#include <fcppt/config/external_begin.hpp>
#include <linux/input.h>
#include <sys/ioctl.h>
#include <array>
#include <fcppt/config/external_end.hpp>


sge::input::info::unique_id
sge::evdev::device::unique_id(
	sge::evdev::device::fd const &_fd
)
{
	typedef
	std::array<
		char,
		1024
	>
	buffer_type;

	buffer_type buffer;

	if(
		::ioctl(
			_fd.get().get(),
			EVIOCGUNIQ(
				buffer.size() - 1
			)
			,
			buffer.data()
		)
		!=
		-1
		&&
		// For whatever reason, Linux used to return empty strings as
		// unique ids. Starting with Linux-4.2, instead of empty
		// strings, an error is returned.
		buffer[0]
		!=
		'\0'
	)
		return
			sge::input::info::unique_id(
				fcppt::from_std_string(
					buffer.data()
				)
			);

	// If there is no unique id, we try to get the physical id instead.
	if(
		::ioctl(
			_fd.get().get(),
			EVIOCGPHYS(
				buffer.size() - 1
			)
			,
			buffer.data()
		)
		==
		-1
	)
		throw
			sge::input::exception{
				FCPPT_TEXT("ioctl EVIOCGPHYS failed")
			};

	return
		sge::input::info::unique_id(
			fcppt::from_std_string(
				buffer.data()
			)
		);
}
