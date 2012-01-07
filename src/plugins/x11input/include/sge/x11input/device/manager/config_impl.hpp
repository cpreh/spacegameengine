/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2012 Carl Philipp Reh (sefi@s-e-f-i.de)

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
#include <fcppt/unique_ptr.hpp>
#include <fcppt/assert/error.hpp>
#include <fcppt/container/ptr/insert_unique_ptr_map.hpp>
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
void
sge::x11input::device::manager::config<
	X11Object,
	DiscoverEvent,
	RemoveEvent
>::initial(
	x11input::create_parameters const &_param
)
{
	this->insert_into_map(
		initial_objects_,
		_param
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
>::add(
	x11input::create_parameters const &_param
)
{
	discover_(
		DiscoverEvent(
			this->insert_into_map(
				objects_,
				_param
			)
		)
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
>::remove(
	x11input::device::id const _id
)
{
	typename object_map::iterator const it(
		objects_.find(
			_id
		)
	);

	FCPPT_ASSERT_ERROR(
		it != objects_.end()
	);

	remove_(
		RemoveEvent(
			*it->second
		)
	);

	objects_.erase(
		it
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
		typename object_map::iterator it(
			initial_objects_.begin()
		);
		it != initial_objects_.end();
		++it
	)
		discover_(
			DiscoverEvent(
				*it->second
			)
		);

	initial_objects_.transfer(
		objects_
	);
}

template<
	typename X11Object,
	typename DiscoverEvent,
	typename RemoveEvent
>
X11Object &
sge::x11input::device::manager::config<
	X11Object,
	DiscoverEvent,
	RemoveEvent
>::insert_into_map(
	object_map &_map,
	x11input::create_parameters const &_param
)
{
	object_unique_ptr object(
		create_(
			_param
		)
	);

	x11input::device::id const id(
		object->id()
	);

	typedef std::pair<
		typename object_map::iterator,
		bool
	> insert_result;

	insert_result const it(
		fcppt::container::ptr::insert_unique_ptr_map(
			_map,
			id,
			fcppt::move(
				object
			)
		)
	);

	FCPPT_ASSERT_ERROR(
		it.second
	);

	return
		*it.first->second;
}

#endif
