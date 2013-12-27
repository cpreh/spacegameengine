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


#include <sge/evdev/logger.hpp>
#include <sge/evdev/device/create_fd.hpp>
#include <sge/evdev/device/fd.hpp>
#include <sge/evdev/device/fd_unique_ptr.hpp>
#include <sge/input/exception.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/text.hpp>
#include <fcppt/error/strerrno.hpp>
#include <fcppt/filesystem/path_to_string.hpp>
#include <fcppt/log/debug.hpp>
#include <fcppt/log/output.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/filesystem/path.hpp>
#include <utility>
#include <fcppt/config/external_end.hpp>


sge::evdev::device::fd_unique_ptr
sge::evdev::device::create_fd(
	boost::filesystem::path const &_path
)
{
	sge::evdev::device::fd_unique_ptr ret(
		fcppt::make_unique_ptr<
			sge::evdev::device::fd
		>(
			_path
		)
	);

	if(
		ret->valid()
	)
		return
			std::move(
				ret
			);

	// Failure for some evdev files is expected.
	FCPPT_LOG_DEBUG(
		sge::evdev::logger(),
		fcppt::log::_
			<<
			FCPPT_TEXT("Opening \"")
			<<
			fcppt::filesystem::path_to_string(
				_path
			)
			<<
			FCPPT_TEXT("\" failed: ")
			<<
			fcppt::error::strerrno()
	);

	return
		sge::evdev::device::fd_unique_ptr();
}
