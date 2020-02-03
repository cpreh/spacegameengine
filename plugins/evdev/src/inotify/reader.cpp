//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/evdev/inotify/convert_event_type.hpp>
#include <sge/evdev/inotify/event.hpp>
#include <sge/evdev/inotify/event_container.hpp>
#include <sge/evdev/inotify/reader.hpp>
#include <awl/backends/posix/fd.hpp>
#include <fcppt/assert/error.hpp>
#include <fcppt/config/external_begin.hpp>
#include <unistd.h>
#include <linux/limits.h>
#include <sys/inotify.h>
#include <array>
#include <cstddef>
#include <cstring>
#include <filesystem>
#include <string>
#include <fcppt/config/external_end.hpp>


sge::evdev::inotify::reader::reader(
	std::filesystem::path const &_path
)
:
	object_{},
	watch_{
		_path,
		object_
	}
{
}

sge::evdev::inotify::reader::~reader()
{
}

sge::evdev::inotify::event_container
sge::evdev::inotify::reader::on_event()
{
	// The manpage says that this is enough to read at least one inotify event
	typedef std::array<
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

	// TODO: Make a range for this
	sge::evdev::inotify::event_container result;

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

		result.push_back(
			sge::evdev::inotify::event{
				std::filesystem::path(
					path_name
				),
				sge::evdev::inotify::convert_event_type(
					event.mask
				)
			}
		);

		index +=
			event.len;
	}

	FCPPT_ASSERT_ERROR(
		index
		==
		bytes
	);

	return
		result;
}

awl::backends::posix::fd
sge::evdev::inotify::reader::fd() const
{
	return
		object_.fd();
}
