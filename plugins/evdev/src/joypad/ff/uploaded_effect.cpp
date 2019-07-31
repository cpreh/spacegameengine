//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/evdev/device/fd.hpp>
#include <sge/evdev/joypad/ff/id.hpp>
#include <sge/evdev/joypad/ff/uploaded_effect.hpp>
#include <sge/input/exception.hpp>
#include <fcppt/text.hpp>
#include <fcppt/assert/error.hpp>
#include <fcppt/config/external_begin.hpp>
#include <linux/input.h>
#include <sys/ioctl.h>
#include <fcppt/config/external_end.hpp>


sge::evdev::joypad::ff::uploaded_effect::uploaded_effect(
	sge::evdev::device::fd const &_fd,
	ff_effect const _effect
)
:
	fd_{
		_fd
	},
	effect_{
		_effect
	}
{
	effect_.id =
		-1;

	if(
		::ioctl(
			fd_.get().get(),
			EVIOCSFF,
			&effect_
		)
		==
		-1
	)
		throw
			sge::input::exception{
				FCPPT_TEXT("Uploading a FF effect failed")
			};
}

sge::evdev::joypad::ff::uploaded_effect::~uploaded_effect()
{
	FCPPT_ASSERT_ERROR(
		::ioctl(
			fd_.get().get(),
			EVIOCRMFF,
			&effect_
		)
		!=
		-1
	);
}

sge::evdev::joypad::ff::id
sge::evdev::joypad::ff::uploaded_effect::id() const
{
	return
		sge::evdev::joypad::ff::id{
			effect_.id
		};
}
