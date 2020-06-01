//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_EVDEV_DEVICE_MAKE_INFO_CONTAINER_HPP_INCLUDED
#define SGE_EVDEV_DEVICE_MAKE_INFO_CONTAINER_HPP_INCLUDED

#include <sge/evdev/device/basic_info_decl.hpp>
#include <sge/evdev/device/event_type.hpp>
#include <sge/evdev/device/event_type_value.hpp>
#include <sge/evdev/device/read_bits_result.hpp>
#include <fcppt/make_int_range_count.hpp>
#include <fcppt/make_literal_strong_typedef.hpp>
#include <fcppt/strong_typedef_construct_cast.hpp>
#include <fcppt/cast/size_fun.hpp>
#include <fcppt/container/bitfield/operators.hpp>
#include <fcppt/config/external_begin.hpp>
#include <utility>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace evdev
{
namespace device
{

template<
	typename Id,
	typename Info,
	sge::evdev::device::event_type_value BitCount,
	typename Function
>
sge::evdev::device::basic_info<
	Id,
	Info
>
make_info_container(
	sge::evdev::device::read_bits_result<
		BitCount
	> const &_bits,
	Function const &_function
)
{
	using
	basic_info
	=
	sge::evdev::device::basic_info<
		Id,
		Info
	>;

	using
	info_container
	=
	typename
	basic_info::info_container;

	using
	result_vector
	=
	typename
	info_container::vector;

	result_vector ids{};

	using
	result_map
	=
	typename
	basic_info::event_map_type;

	result_map event_map{};

	using
	bit_container
	=
	sge::evdev::device::read_bits_result<
		BitCount
	>;

	for(
		sge::evdev::device::event_type const index
		:
		fcppt::make_int_range_count(
			sge::evdev::device::event_type{
				bit_container::static_size::value
			}
		)
	)
	{
		if(
			_bits
			&
			index.get()
		)
		{
			event_map.insert(
				std::make_pair(
					index,
					fcppt::strong_typedef_construct_cast<
						typename basic_info::id,
						fcppt::cast::size_fun
					>(
						ids.size()
					)
				)
			);

			ids.push_back(
				_function(
					index
				)
			);
		}
	}

	return
		basic_info(
			info_container(
				std::move(
					ids
				)
			),
			std::move(
				event_map
			)
		);
}

}
}
}

#endif
