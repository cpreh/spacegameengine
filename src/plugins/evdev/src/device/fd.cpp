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


#include <sge/evdev/device/fd.hpp>
#include <awl/backends/linux/fd/object.hpp>
#include <fcppt/assert/pre.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/filesystem/path.hpp>
#include <sys/stat.h>
#include <sys/types.h>
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
}

sge::evdev::device::fd::~fd()
{
	if(
		this->valid()
	)
		::close(
			fd_.get()
		);
}

awl::backends::linux::fd::object const
sge::evdev::device::fd::get() const
{
	FCPPT_ASSERT_PRE(
		this->valid()
	);

	return
		fd_;
}

bool
sge::evdev::device::fd::valid() const
{
	return
		fd_.get() != -1;
}
