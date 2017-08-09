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


#ifndef SGE_WLINPUT_REMOVE_SEAT_HPP_INCLUDED
#define SGE_WLINPUT_REMOVE_SEAT_HPP_INCLUDED

#include <sge/wlinput/map.hpp>
#include <awl/backends/wayland/system/seat/caps.hpp>
#include <awl/backends/wayland/system/seat/caps_field.hpp>
#include <awl/backends/wayland/system/seat/object.hpp>
#include <awl/event/base.hpp>
#include <awl/event/optional_base_unique_ptr.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/shared_ptr_impl.hpp>
#include <fcppt/unique_ptr_to_base.hpp>
#include <fcppt/container/find_opt_iterator.hpp>
#include <fcppt/container/bitfield/operators.hpp>
#include <fcppt/optional/join.hpp>
#include <fcppt/optional/make_if.hpp>
#include <fcppt/optional/map.hpp>
#include <fcppt/preprocessor/disable_gcc_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>


namespace sge
{
namespace wlinput
{

template<
	awl::backends::wayland::system::seat::caps Caps,
	typename RemoveEvent,
	typename Object
>
awl::event::optional_base_unique_ptr
remove_seat(
	sge::wlinput::map<
		Object
	> &_map,
	awl::backends::wayland::system::seat::object const &_seat
)
{
	typedef
	sge::wlinput::map<
		Object
	>
	object_map;

	FCPPT_PP_PUSH_WARNING
	FCPPT_PP_DISABLE_GCC_WARNING(-Wattributes)

	auto const make_event(
		[
			&_map,
			&_seat
		]{
			return
				fcppt::optional::map(
					fcppt::container::find_opt_iterator(
						_map,
						_seat.name()
					),
					[
						&_map
					](
						typename
						object_map::iterator const _iterator
					)
					{
						awl::event::base_unique_ptr event{
							fcppt::unique_ptr_to_base<
								awl::event::base
							>(
								fcppt::make_unique_ptr<
									RemoveEvent
								>(
									_iterator->second
								)
							)
						};

						_map.erase(
							_iterator
						);

						return
							event;
					}
				);
		}
	);

	FCPPT_PP_POP_WARNING

	return
		fcppt::optional::join(
			fcppt::optional::make_if(
				_seat.caps()
				&
				Caps,
				make_event
			)
		);
}

}
}

#endif
