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


#include <sge/evdev/focus_manager.hpp>
#include <sge/evdev/device/event.hpp>
#include <sge/evdev/device/fd.hpp>
#include <sge/evdev/device/fd_unique_ptr.hpp>
#include <sge/evdev/device/object.hpp>
#include <sge/input/exception.hpp>
#include <awl/backends/linux/fd/callback.hpp>
#include <awl/backends/linux/fd/event_fwd.hpp>
#include <awl/backends/linux/fd/processor.hpp>
#include <fcppt/text.hpp>
#include <fcppt/signal/auto_connection.hpp>
#include <fcppt/config/external_begin.hpp>
#include <linux/input.h>
#include <cerrno>
#include <unistd.h>
#include <utility>
#include <fcppt/config/external_end.hpp>


sge::evdev::device::object::object(
	sge::evdev::focus_manager const &_focus_manager,
	awl::backends::linux::fd::processor &_processor,
	sge::evdev::device::fd_unique_ptr _fd
)
:
	focus_manager_(
		_focus_manager
	),
	fd_(
		std::move(
			_fd
		)
	),
	scoped_connection_(
		_processor.register_fd_callback(
			fd_->get(),
			awl::backends::linux::fd::callback(
				std::bind(
					&sge::evdev::device::object::on_event,
					this,
					std::placeholders::_1
				)
			)
		)
	)
{
}

sge::evdev::device::object::~object()
{
}

void
sge::evdev::device::object::on_event(
	awl::backends::linux::fd::event const &
)
{
	ssize_t result = -1;

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
	{
		if(
			focus_manager_.focus()
		)
			this->process_event(
				sge::evdev::device::event(
					event
				)
			);
	}

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
