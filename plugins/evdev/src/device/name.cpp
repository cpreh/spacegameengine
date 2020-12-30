//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/evdev/device/fd.hpp>
#include <sge/evdev/device/name.hpp>
#include <sge/input/exception.hpp>
#include <sge/input/info/name.hpp>
#include <fcppt/from_std_string.hpp>
#include <fcppt/no_init.hpp>
#include <fcppt/text.hpp>
#include <fcppt/array/object_impl.hpp>
#include <fcppt/config/external_begin.hpp>
#include <linux/input.h>
#include <sys/ioctl.h>
#include <fcppt/config/external_end.hpp>


sge::input::info::name
sge::evdev::device::name(
	sge::evdev::device::fd &_fd
)
{
	using
	buffer_type
	=
	fcppt::array::object<
		char,
		1024 // NOLINT(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)
	>;

	buffer_type buffer{
		fcppt::no_init{}
	};

	if(
		::ioctl( // NOLINT(cppcoreguidelines-pro-type-vararg,hicpp-vararg)
			_fd.get().get(),
			EVIOCGNAME( // NOLINT(hicpp-signed-bitwise)
				buffer.size() - 1
			)
			,
			buffer.data()
		)
		==
		-1
	)
	{
		throw
			sge::input::exception{
				FCPPT_TEXT("ioctl EVIOCGNAME failed")
			};
	}

	return
		sge::input::info::name(
			fcppt::from_std_string(
				buffer.data()
			)
		);
}
