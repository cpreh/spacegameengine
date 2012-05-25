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


#include <sge/evdev/eventfd/fd.hpp>
#include <sge/input/exception.hpp>
#include <awl/backends/linux/fd/object.hpp>
#include <fcppt/text.hpp>
#include <fcppt/config/external_begin.hpp>
#include <sys/eventfd.h>
#include <unistd.h>
#include <fcppt/config/external_end.hpp>


sge::evdev::eventfd::fd::fd()
:
	fd_(
		::eventfd(
			0u,
			0
		)
	)
{
	if(
		fd_.get() == -1
	)
		throw sge::input::exception(
			FCPPT_TEXT("eventfd failed")
		);
}


sge::evdev::eventfd::fd::~fd()
{
	::close(
		fd_.get()
	);
}

awl::backends::linux::fd::object const
sge::evdev::eventfd::fd::get() const
{
	return
		fd_;
}
