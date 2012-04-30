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
#include <sge/input/exception.hpp>
#include <awl/backends/x11/event/fd/callback.hpp>
#include <awl/backends/x11/event/fd/event_fwd.hpp>
#include <awl/backends/x11/system/event/processor.hpp>
#include <fcppt/assert/error.hpp>
#include <fcppt/assert/throw.hpp>
#include <fcppt/container/raw_vector_impl.hpp>
#include <fcppt/signal/auto_connection.hpp>
#include <fcppt/tr1/functional.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/filesystem/path.hpp>
#include <sys/inotify.h>
#include <unistd.h>
#include <cerrno>
#include <fcppt/config/external_end.hpp>


sge::evdev::inotify::reader::reader(
	boost::filesystem::path const &_path,
	awl::backends::x11::system::event::processor &_processor,
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
			awl::backends::x11::event::fd::callback(
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
	awl::backends::x11::event::fd::event const &
)
{
	inotify_event event;

	{
		ssize_t ret(
			::read(
				object_.fd().get(),
				&event,
				sizeof(
					inotify_event
				)
			)
		);

		if(
			(
				ret == -1
				&&
				(
					errno == EINVAL
					||
					errno == EAGAIN
				)
			)
			||
			ret == 0
		)
			return;

		FCPPT_ASSERT_THROW(
			ret
			==
			static_cast<
				ssize_t
			>(
				sizeof(
					inotify_event
				)
			),
			sge::input::exception
		);
	}

	typedef fcppt::container::raw_vector<
		char
	> char_vector;

	char_vector name(
		event.len
	);

	FCPPT_ASSERT_ERROR(
		event.len > 0
	);

	{
		ssize_t ret(
			::read(
				object_.fd().get(),
				name.data(),
				name.size()
			)
		);

		FCPPT_ASSERT_THROW(
			ret
			==
			static_cast<
				ssize_t
			>(
				event.len
			),
			sge::input::exception
		);
	}

	callback_(
		sge::evdev::inotify::event(
			boost::filesystem::path(
				name.data()
			),
			sge::evdev::inotify::convert_event_type(
				event.mask
			)
		)
	);
}
