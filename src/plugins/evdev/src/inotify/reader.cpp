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


#include <sge/evdev/inotify/callback.hpp>
#include <sge/evdev/inotify/convert_event_type.hpp>
#include <sge/evdev/inotify/event.hpp>
#include <sge/evdev/inotify/reader.hpp>
#include <awl/backends/linux/fd/callback.hpp>
#include <awl/backends/linux/fd/event_fwd.hpp>
#include <awl/backends/linux/fd/processor.hpp>
#include <fcppt/assert/error.hpp>
#include <fcppt/container/array_impl.hpp>
#include <fcppt/signal/auto_connection.hpp>
#include <fcppt/tr1/functional.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/filesystem/path.hpp>
#include <linux/limits.h>
#include <sys/inotify.h>
#include <unistd.h>
#include <cstddef>
#include <string>
#include <fcppt/config/external_end.hpp>


sge::evdev::inotify::reader::reader(
	boost::filesystem::path const &_path,
	awl::backends::linux::fd::processor &_processor,
	sge::evdev::inotify::callback const &_callback
)
:
	object_(),
	watch_(
		_path,
		object_
	),
	fd_connection_(
		_processor.register_fd_callback(
			object_.fd(),
			awl::backends::linux::fd::callback(
				std::tr1::bind(
					&sge::evdev::inotify::reader::on_read,
					this,
					std::tr1::placeholders::_1
				)
			)
		)
	),
	callback_(
		_callback
	)
{
}

sge::evdev::inotify::reader::~reader()
{
}

void
sge::evdev::inotify::reader::on_read(
	awl::backends::linux::fd::event const &
)
{
	// The manpage says that this is enough to read at least one inotify event
	typedef fcppt::container::array<
		char,
		sizeof(
			inotify_event
		)
		+
		NAME_MAX
		+
		1u
	> buffer_array;

	buffer_array buffer;

	ssize_t ret(
		::read(
			object_.fd().get(),
			buffer.data(),
			buffer.size()
		)
	);

	FCPPT_ASSERT_ERROR(
		ret != -1
	);

	std::size_t const bytes(
		static_cast<
			std::size_t
		>(
			ret
		)
	);

	std::size_t index(
		0u
	);

	while(
		index
		<
		bytes
	)
	{
		FCPPT_ASSERT_ERROR(
			bytes
			-
			index
			>=
			sizeof(
				inotify_event
			)
		);

		inotify_event event;

		std::memcpy(
			&event,
			buffer.data() + index,
			sizeof(
				inotify_event
			)
		);

		FCPPT_ASSERT_ERROR(
			event.len != 0u
		);

		index +=
			sizeof(
				inotify_event
			);

		std::string const path_name(
			buffer.data() + index
		);

		callback_(
			sge::evdev::inotify::event(
				boost::filesystem::path(
					path_name
				),
				sge::evdev::inotify::convert_event_type(
					event.mask
				)
			)
		);

		index +=
			event.len;
	}

	FCPPT_ASSERT_ERROR(
		index
		==
		bytes
	);
}
