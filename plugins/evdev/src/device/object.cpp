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
#include <awl/backends/posix/fd.hpp>
#include <awl/backends/posix/processor.hpp>
#include <awl/event/base.hpp>
#include <awl/event/base_unique_ptr.hpp>
#include <awl/event/connection.hpp>
#include <awl/event/container.hpp>
#include <fcppt/text.hpp>
#include <fcppt/optional/maybe_void.hpp>
#include <fcppt/config/external_begin.hpp>
#include <linux/input.h>
#include <boost/filesystem/path.hpp>
#include <cerrno>
#include <unistd.h>
#include <utility>
#include <fcppt/config/external_end.hpp>


sge::evdev::device::object::object(
	sge::evdev::device::fd_unique_ptr &&_fd,
	awl::backends::posix::processor &_processor,
	boost::filesystem::path const &_path
)
:
	fd_{
		std::move(
			_fd
		)
	},
	fd_connection_{
		_processor.register_fd(
			this->fd_->get()
		)
	},
	path_{
		_path
	}
{
}

sge::evdev::device::object::~object()
{
}

awl::event::container
sge::evdev::device::object::on_event()
{
	ssize_t result{
		-1
	};

	input_event event;

	// TODO: Make a range for this
	awl::event::container events{};

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
		fcppt::optional::maybe_void(
			this->process_event(
				sge::evdev::device::event(
					event
				)
			),
			[
				&events
			](
				awl::event::base_unique_ptr &&_event
			)
			{
				events.push_back(
					std::move(
						_event
					)
				);
			}
		);

	if(
		result
		==
		-1
		&&
		errno
		!=
		EAGAIN
	)
		throw
			sge::input::exception{
				FCPPT_TEXT("Reading a device failed")
			};

	return
		events;
}

awl::backends::posix::fd
sge::evdev::device::object::posix_fd() const
{
	return
		this->fd().get();
}

boost::filesystem::path const &
sge::evdev::device::object::path() const
{
	return
		path_;
}

sge::evdev::device::fd const &
sge::evdev::device::object::fd() const
{
	return
		*fd_;
}
