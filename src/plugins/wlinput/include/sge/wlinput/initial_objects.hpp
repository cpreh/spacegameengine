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


#ifndef SGE_WLINPUT_INITIAL_OBJECTS_HPP_INCLUDED
#define SGE_WLINPUT_INITIAL_OBJECTS_HPP_INCLUDED

#include <awl/backends/wayland/registry_id.hpp>
#include <awl/backends/wayland/system/seat/caps.hpp>
#include <awl/backends/wayland/system/seat/object.hpp>
#include <awl/backends/wayland/system/seat/set.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/unique_ptr_impl.hpp>
#include <fcppt/algorithm/map_optional.hpp>
#include <fcppt/container/bitfield/operators.hpp>
#include <fcppt/optional/object_impl.hpp>
#include <fcppt/config/external_begin.hpp>
#include <unordered_map>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace wlinput
{

template<
	typename Type,
	awl::backends::wayland::system::seat::caps Caps
>
std::unordered_map<
	awl::backends::wayland::registry_id,
	fcppt::unique_ptr<
		Type
	>
>
initial_objects(
	awl::backends::wayland::system::seat::set const &_seats
)
{
	typedef
	std::unordered_map<
		awl::backends::wayland::registry_id,
		fcppt::unique_ptr<
			Type
		>
	>
	result_type;

	return
		fcppt::algorithm::map_optional<
			result_type
		>(
			_seats,
			[](
				awl::backends::wayland::system::seat::object const &_seat
			)
			{
				typedef
				typename
				result_type::value_type
				value_type;

				typedef
				fcppt::optional::object<
					value_type
				>
				optional_value_type;

				return
					_seat.caps()
					&
					Caps
					?
						optional_value_type{
							value_type{
								_seat.name(),
								fcppt::make_unique_ptr<
									Type
								>(
									_seat.get()
								)
							}
						}
					:
						optional_value_type{}
					;
			}
		);
}

}
}

#endif
