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


#ifndef SGE_X11INPUT_DEVICE_MANAGER_CONFIG_IMPL_HPP_INCLUDED
#define SGE_X11INPUT_DEVICE_MANAGER_CONFIG_IMPL_HPP_INCLUDED

#include <sge/x11input/create_parameters_fwd.hpp>
#include <sge/x11input/device/id.hpp>
#include <sge/x11input/device/object.hpp>
#include <sge/x11input/device/manager/config.hpp>
#include <fcppt/const.hpp>
#include <fcppt/make_ref.hpp>
#include <fcppt/reference_impl.hpp>
#include <fcppt/reference_to_base.hpp>
#include <fcppt/assert/error.hpp>
#include <fcppt/container/find_opt_iterator.hpp>
#include <fcppt/optional/maybe.hpp>
#include <fcppt/optional/reference.hpp>
#include <fcppt/signal/object.hpp>
#include <fcppt/config/external_begin.hpp>
#include <utility>
#include <fcppt/config/external_end.hpp>


template<
	typename X11Object,
	typename DiscoverEvent,
	typename RemoveEvent
>
sge::x11input::device::manager::config<
	X11Object,
	DiscoverEvent,
	RemoveEvent
>::config(
	discover_signal &_discover,
	remove_signal &_remove,
	create_function const &_create
)
:
	objects_(),
	initial_objects_(),
	discover_(
		_discover
	),
	remove_(
		_remove
	),
	create_(
		_create
	)
{
}

template<
	typename X11Object,
	typename DiscoverEvent,
	typename RemoveEvent
>
sge::x11input::device::manager::config<
	X11Object,
	DiscoverEvent,
	RemoveEvent
>::~config()
{
}

template<
	typename X11Object,
	typename DiscoverEvent,
	typename RemoveEvent
>
bool
sge::x11input::device::manager::config<
	X11Object,
	DiscoverEvent,
	RemoveEvent
>::initial(
	sge::x11input::create_parameters const &_param
)
{
	this->insert_into_map(
		initial_objects_,
		_param
	);

	return
		true;
}

template<
	typename X11Object,
	typename DiscoverEvent,
	typename RemoveEvent
>
bool
sge::x11input::device::manager::config<
	X11Object,
	DiscoverEvent,
	RemoveEvent
>::add(
	sge::x11input::create_parameters const &_param
)
{
	return
		fcppt::optional::maybe(
			this->insert_into_map(
				objects_,
				_param
			),
			fcppt::const_(
				false
			),
			[
				this
			](
				fcppt::reference<
					X11Object
				> const _object
			)
			{
				discover_(
					DiscoverEvent(
						_object.get()
					)
				);

				return
					true;
			}
		);
}

template<
	typename X11Object,
	typename DiscoverEvent,
	typename RemoveEvent
>
bool
sge::x11input::device::manager::config<
	X11Object,
	DiscoverEvent,
	RemoveEvent
>::remove(
	sge::x11input::device::id const _id
)
{
	return
		fcppt::optional::maybe(
			fcppt::container::find_opt_iterator(
				objects_,
				_id
			),
			fcppt::const_(
				false
			),
			[
				this
			](
				typename object_map::iterator const _it
			)
			{
				remove_(
					RemoveEvent(
						*_it->second
					)
				);

				objects_.erase(
					_it
				);

				return
					true;
			}
		);
}

template<
	typename X11Object,
	typename DiscoverEvent,
	typename RemoveEvent
>
void
sge::x11input::device::manager::config<
	X11Object,
	DiscoverEvent,
	RemoveEvent
>::dispatch_initial()
{
	for(
		auto const &object
		:
		initial_objects_
	)
		discover_(
			DiscoverEvent(
				*object.second
			)
		);

	objects_ =
		std::move(
			initial_objects_
		);

	for(
		auto const &object
		:
		objects_
	)
		object.second->init();
}

template<
	typename X11Object,
	typename DiscoverEvent,
	typename RemoveEvent
>
typename
sge::x11input::device::manager::config<
	X11Object,
	DiscoverEvent,
	RemoveEvent
>::optional_object_ref
sge::x11input::device::manager::config<
	X11Object,
	DiscoverEvent,
	RemoveEvent
>::insert_into_map(
	object_map &_map,
	sge::x11input::create_parameters const &_param
)
{
	object_unique_ptr object(
		create_(
			_param
		)
	);

	sge::x11input::device::id const id(
		object->id()
	);

	typedef
	std::pair<
		typename
		object_map::iterator,
		bool
	>
	insert_result;

	insert_result const it(
		_map.insert(
			std::make_pair(
				id,
				std::move(
					object
				)
			)
		)
	);

	FCPPT_ASSERT_ERROR(
		it.second
	);

	return
		optional_object_ref(
			fcppt::make_ref(
				*it.first->second
			)
		);
}

#endif
