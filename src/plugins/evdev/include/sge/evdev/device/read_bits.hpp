/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2013 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#ifndef SGE_EVDEV_DEVICE_READ_BITS_HPP_INCLUDED
#define SGE_EVDEV_DEVICE_READ_BITS_HPP_INCLUDED

#include <sge/evdev/device/event_type_value.hpp>
#include <sge/evdev/device/fd.hpp>
#include <sge/evdev/device/read_bits_result.hpp>
#include <sge/input/exception.hpp>
#include <fcppt/no_init.hpp>
#include <fcppt/text.hpp>
#include <fcppt/container/bitfield/object_impl.hpp>
#include <fcppt/config/external_begin.hpp>
#include <linux/input.h>
#include <sys/ioctl.h>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace evdev
{
namespace device
{

template<
	sge::evdev::device::event_type_value Count
>
typename sge::evdev::device::read_bits_result<
	Count
>::type const
read_bits(
	sge::evdev::device::fd const &_fd,
	unsigned const _type
)
{
	typedef typename sge::evdev::device::read_bits_result<
		Count
	>::type result_type;

	result_type result{
		fcppt::no_init()
	};

	if(
		::ioctl(
			_fd.get().get(),
			EVIOCGBIT(
				_type,
				static_cast<
					unsigned
				>(
					result.size()
				)
			),
			result.data()
		)
		==
		-1
	)
		throw sge::input::exception(
			FCPPT_TEXT("ioctl reading device capabilities failed!")
		);

	return
		result;
}

}
}
}

#endif
