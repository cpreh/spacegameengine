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


#include <sge/evdev/device/fd.hpp>
#include <sge/evdev/joypad/ff/make_info.hpp>
#include <sge/input/exception.hpp>
#include <sge/input/joypad/ff/type.hpp>
#include <sge/input/joypad/ff/type_field.hpp>
#include <fcppt/make_enum_range.hpp>
#include <fcppt/text.hpp>
#include <fcppt/assert/unreachable.hpp>
#include <fcppt/container/bitfield/object_from_enum.hpp>
#include <fcppt/config/external_begin.hpp>
#include <linux/input.h>
#include <sys/ioctl.h>
#include <fcppt/config/external_end.hpp>


namespace
{

// These are contiguous
enum class linux_effect{
	periodic = FF_PERIODIC,
	constant = FF_CONSTANT,
	spring = FF_SPRING,
	friction = FF_FRICTION,
	damper = FF_DAMPER,
	inertia = FF_INERTIA,
	ramp = FF_RAMP,
	square = FF_SQUARE,
	triangle = FF_TRIANGLE,
	sine = FF_SINE,
	saw_up = FF_SAW_UP,
	saw_down = FF_SAW_DOWN,
	custom = FF_CUSTOM,
	fcppt_maximum = FF_CNT
};

linux_effect
to_linux_effect(
	sge::input::joypad::ff::type const _type
)
{
#define SGE_TO_LINUX_EFFECT_CASE(\
	name \
) \
	case sge::input::joypad::ff::type:: name: \
		return \
			linux_effect:: name

	switch(
		_type
	)
	{
		SGE_TO_LINUX_EFFECT_CASE(
			constant
		);
		SGE_TO_LINUX_EFFECT_CASE(
			spring
		);
		SGE_TO_LINUX_EFFECT_CASE(
			friction
		);
		SGE_TO_LINUX_EFFECT_CASE(
			damper
		);
		SGE_TO_LINUX_EFFECT_CASE(
			inertia
		);
		SGE_TO_LINUX_EFFECT_CASE(
			ramp
		);
		SGE_TO_LINUX_EFFECT_CASE(
			square
		);
		SGE_TO_LINUX_EFFECT_CASE(
			sine
		);
		SGE_TO_LINUX_EFFECT_CASE(
			saw_up
		);
		SGE_TO_LINUX_EFFECT_CASE(
			saw_down
		);
		SGE_TO_LINUX_EFFECT_CASE(
			custom
		);
	}

#undef SGE_TO_LINUX_EFFECT_CASE

	FCPPT_ASSERT_UNREACHABLE;
}

}

sge::input::joypad::ff::type_field
sge::evdev::joypad::ff::make_info(
	sge::evdev::device::fd const &_fd
)
{
	typedef
	unsigned long
	int_type;

	typedef
	fcppt::container::bitfield::object_from_enum<
		linux_effect,
		int_type
	>
	linux_buffer;

	linux_buffer buffer(
		linux_buffer::null()
	);

	if(
		::ioctl(
			_fd.get().get(),
			EVIOCGBIT(
				EV_FF,
				buffer.array().size()
				*
				sizeof(
					int_type
				)
			),
			buffer.array().data()
		)
		==
		-1
	)
		throw
			sge::input::exception{
				FCPPT_TEXT("EV_FF failed")
			};

	sge::input::joypad::ff::type_field result(
		sge::input::joypad::ff::type_field::null()
	);

	// TODO: Make an algorithm for this
	for(
		sge::input::joypad::ff::type const type
		:
		fcppt::make_enum_range<
			sge::input::joypad::ff::type
		>()
	)
		if(
			buffer.get(
				to_linux_effect(
					type
				)
			)
		)
			result.set(
				type,
				true
			);

	return
		result;
}
