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
#include <fcppt/signal/object.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/spirit/home/phoenix/bind/bind_member_function.hpp>
#include <boost/spirit/home/phoenix/core/argument.hpp>
#include <boost/spirit/home/phoenix/operator/comparison.hpp>
#include <boost/spirit/home/phoenix/operator/self.hpp>
#include <algorithm>
#include <fcppt/config/external_end.hpp>


template<
	typename X11ObjectPtr,
	typename DiscoverEvent,
	typename RemoveEvent
>
sge::x11input::device::manager::config<
	X11ObjectPtr,
	DiscoverEvent,
	RemoveEvent
>::config(
	object_vector &_objects,
	discover_signal &_discover,
	remove_signal &_remove,
	create_function const &_create
)
:
	objects_(_objects),
	discover_(_discover),
	remove_(_remove),
	create_(_create)
{
}

template<
	typename X11ObjectPtr,
	typename DiscoverEvent,
	typename RemoveEvent
>
sge::x11input::device::manager::config<
	X11ObjectPtr,
	DiscoverEvent,
	RemoveEvent
>::~config()
{
}

template<
	typename X11ObjectPtr,
	typename DiscoverEvent,
	typename RemoveEvent
>
void
sge::x11input::device::manager::config<
	X11ObjectPtr,
	DiscoverEvent,
	RemoveEvent
>::initial(
	x11input::create_parameters const &_param
)
{
	X11ObjectPtr const obj(
		create_(
			_param
		)
	);

	if(
		obj
	)
		objects_.push_back(
			obj
		);
}

template<
	typename X11ObjectPtr,
	typename DiscoverEvent,
	typename RemoveEvent
>
void
sge::x11input::device::manager::config<
	X11ObjectPtr,
	DiscoverEvent,
	RemoveEvent
>::add(
	x11input::create_parameters const &_param
)
{
	X11ObjectPtr const obj(
		create_(
			_param
		)
	);

	if(
		!obj
	)
		return;

	objects_.push_back(
		obj
	);

	discover_(
		DiscoverEvent(
			obj
		)
	);
}

template<
	typename X11ObjectPtr,
	typename DiscoverEvent,
	typename RemoveEvent
>
void
sge::x11input::device::manager::config<
	X11ObjectPtr,
	DiscoverEvent,
	RemoveEvent
>::remove(
	x11input::device::id const _id
)
{
	typename object_vector::iterator const it(
		std::find_if(
			objects_.begin(),
			objects_.end(),
			boost::phoenix::bind(
				&x11input::device::object::id,
				*boost::phoenix::arg_names::arg1
			)
			==
			_id
		)
	);

	if(
		it == objects_.end()
	)
		return;

	X11ObjectPtr const ptr(
		*it
	);

	objects_.erase(
		it
	);

	remove_(
		RemoveEvent(
			ptr
		)
	);
}

#endif
