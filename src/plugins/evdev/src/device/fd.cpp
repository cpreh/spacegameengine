/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2012 Carl Philipp Reh (sefi@s-e-f-i.de)

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
#include <sge/input/exception.hpp>
#include <awl/backends/x11/event/fd/object.hpp>
#include <fcppt/text.hpp>
#include <fcppt/error/strerrno.hpp>
#include <fcppt/filesystem/path_to_string.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/filesystem/path.hpp>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <fcppt/config/external_end.hpp>


sge::evdev::device::fd::fd(
	boost::filesystem::path const &_path
)
:
	fd_(
		::open(
			_path.string().c_str(),
			O_RDONLY | O_NONBLOCK
		)
	)
{
	if(
		fd_.get() == -1
	)
		throw sge::input::exception(
			FCPPT_TEXT("Opening \"")
			+
			fcppt::filesystem::path_to_string(
				_path
			)
			+
			FCPPT_TEXT("\" failed: ")
			+
			fcppt::error::strerrno()
		);
}

sge::evdev::device::fd::~fd()
{
	::close(
		fd_.get()
	);
}

awl::backends::x11::event::fd::object const
sge::evdev::device::fd::get() const
{
	return
		fd_;
}
