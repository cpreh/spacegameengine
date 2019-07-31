//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/evdev/device/fd.hpp>
#include <sge/evdev/device/unique_id.hpp>
#include <sge/input/exception.hpp>
#include <sge/input/info/unique_id.hpp>
#include <fcppt/from_std_string.hpp>
#include <fcppt/text.hpp>
#include <fcppt/config/external_begin.hpp>
#include <linux/input.h>
#include <sys/ioctl.h>
#include <array>
#include <fcppt/config/external_end.hpp>


sge::input::info::unique_id
sge::evdev::device::unique_id(
	sge::evdev::device::fd const &_fd
)
{
	typedef
	std::array<
		char,
		1024
	>
	buffer_type;

	buffer_type buffer;

	if(
		::ioctl(
			_fd.get().get(),
			EVIOCGUNIQ(
				buffer.size() - 1
			)
			,
			buffer.data()
		)
		!=
		-1
		&&
		// For whatever reason, Linux used to return empty strings as
		// unique ids. Starting with Linux-4.2, instead of empty
		// strings, an error is returned.
		buffer[0]
		!=
		'\0'
	)
		return
			sge::input::info::unique_id(
				fcppt::from_std_string(
					buffer.data()
				)
			);

	// If there is no unique id, we try to get the physical id instead.
	if(
		::ioctl(
			_fd.get().get(),
			EVIOCGPHYS(
				buffer.size() - 1
			)
			,
			buffer.data()
		)
		==
		-1
	)
		throw
			sge::input::exception{
				FCPPT_TEXT("ioctl EVIOCGPHYS failed")
			};

	return
		sge::input::info::unique_id(
			fcppt::from_std_string(
				buffer.data()
			)
		);
}
