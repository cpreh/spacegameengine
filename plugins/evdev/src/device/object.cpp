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


#include <sge/evdev/device/event.hpp>
#include <sge/evdev/device/fd.hpp>
#include <sge/evdev/device/fd_unique_ptr.hpp>
#include <sge/evdev/device/object.hpp>
#include <sge/input/exception.hpp>
#include <awl/backends/posix/callback.hpp>
#include <awl/backends/posix/event_fwd.hpp>
#include <awl/backends/posix/processor.hpp>
#include <fcppt/text.hpp>
#include <fcppt/signal/auto_connection.hpp>
#include <fcppt/config/external_begin.hpp>
#include <linux/input.h>
#include <cerrno>
#include <unistd.h>
#include <utility>
#include <fcppt/config/external_end.hpp>


sge::evdev::device::object::object(
	awl::backends::posix::processor &_processor,
	sge::evdev::device::fd_unique_ptr _fd
)
:
	fd_(
		std::move(
			_fd
		)
	),
	auto_connection_(
		_processor.register_fd_callback(
			fd_->get(),
			awl::backends::posix::callback{
				std::bind(
					&sge::evdev::device::object::on_event,
					this,
					std::placeholders::_1
				)
			}
		)
	)
{
}

sge::evdev::device::object::~object()
{
}

void
sge::evdev::device::object::on_event(
	awl::backends::posix::event const &
)
{
	ssize_t result{
		-1
	};

	input_event event;

	while(
		(
			result
			=
			::read(
				fd_->get().get(),
				&event,
				sizeof(
					event
				)
			)
		)
		> 0
	)
		this->process_event(
			sge::evdev::device::event(
				event
			)
		);

	if(
		result == -1
		&&
		errno
		!=
		EAGAIN
	)
		throw sge::input::exception{
			FCPPT_TEXT("Reading a device failed")
		};
}


sge::evdev::device::fd const &
sge::evdev::device::object::fd() const
{
	return
		*fd_;
}
