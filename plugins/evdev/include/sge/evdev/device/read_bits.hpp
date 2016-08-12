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


#ifndef SGE_EVDEV_DEVICE_READ_BITS_HPP_INCLUDED
#define SGE_EVDEV_DEVICE_READ_BITS_HPP_INCLUDED

#include <sge/evdev/device/event_type_value.hpp>
#include <sge/evdev/device/fd.hpp>
#include <sge/evdev/device/read_bits_result.hpp>
#include <sge/input/exception.hpp>
#include <fcppt/text.hpp>
#include <fcppt/cast/size.hpp>
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
sge::evdev::device::read_bits_result<
	Count
>
read_bits(
	sge::evdev::device::fd const &_fd,
	unsigned const _type
)
{
	typedef
	sge::evdev::device::read_bits_result<
		Count
	>
	result_type;

	typedef
	typename
	result_type::array_type
	array_type;

	array_type result;

	if(
		::ioctl(
			_fd.get().get(),
			EVIOCGBIT(
				_type,
				fcppt::cast::size<
					unsigned
				>(
					Count
				)
			),
			result.data()
		)
		==
		-1
	)
		throw
			sge::input::exception{
				FCPPT_TEXT("ioctl reading device capabilities failed!")
			};

	return
		result_type(
			result
		);
}

}
}
}

#endif
