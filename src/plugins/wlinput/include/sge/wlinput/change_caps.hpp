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


#ifndef SGE_WLINPUT_CHANGE_CAPS_HPP_INCLUDED
#define SGE_WLINPUT_CHANGE_CAPS_HPP_INCLUDED

#include <sge/input/event/discover.hpp>
#include <sge/input/event/remove.hpp>
#include <awl/backends/wayland/registry_id.hpp>
#include <awl/backends/wayland/system/seat/caps.hpp>
#include <awl/backends/wayland/system/seat/caps_field.hpp>
#include <awl/backends/wayland/system/seat/object.hpp>
#include <awl/backends/wayland/window/object_fwd.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/unique_ptr_impl.hpp>
#include <fcppt/assert/error.hpp>
#include <fcppt/container/find_opt_iterator.hpp>
#include <fcppt/container/bitfield/operators.hpp>
#include <fcppt/optional/maybe_void.hpp>
#include <fcppt/signal/object_impl.hpp>
#include <fcppt/config/external_begin.hpp>
#include <unordered_map>
#include <utility>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace wlinput
{

template<
	awl::backends::wayland::system::seat::caps Caps,
	typename Object,
	typename Base
>
void
change_caps(
	awl::backends::wayland::window::object const &_window,
	std::unordered_map<
		awl::backends::wayland::registry_id,
		fcppt::unique_ptr<
			Object
		>
	> &_map,
	fcppt::signal::object<
		void (
			sge::input::event::discover<
				Base
			> const &
		)
	> &_discover_signal,
	fcppt::signal::object<
		void (
			sge::input::event::remove<
				Base
			> const &
		)
	> &_remove_signal,
	awl::backends::wayland::system::seat::object const &_seat
)
{
	typedef
	std::unordered_map<
		awl::backends::wayland::registry_id,
		fcppt::unique_ptr<
			Object
		>
	>
	object_map;

	if(
		_seat.caps()
		&
		Caps
	)
	{
		if(
			_map.count(
				_seat.name()
			)
			==
			0u
		)
		{
			std::pair<
				typename
				object_map::iterator,
				bool
			> const result{
				_map.insert(
					std::make_pair(
						_seat.name(),
						fcppt::make_unique_ptr<
							Object
						>(
							_window,
							_seat.get()
						)
					)
				)
			};

			FCPPT_ASSERT_ERROR(
				result.second
			);

			_discover_signal(
				sge::input::event::discover<
					Base
				>{
					*result.first->second
				}
			);
		}
	}
	else
	{
		fcppt::optional::maybe_void(
			fcppt::container::find_opt_iterator(
				_map,
				_seat.name()
			),
			[
				&_remove_signal,
				&_map
			](
				typename
				object_map::iterator const _iterator
			)
			{
				_remove_signal(
					sge::input::event::remove<
						Base
					>{
						*_iterator->second
					}
				);

				_map.erase(
					_iterator
				);
			}
		);
	}
}

}
}

#endif
