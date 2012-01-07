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


#ifndef SGE_X11INPUT_DEVICE_MANAGER_CONFIG_HPP_INCLUDED
#define SGE_X11INPUT_DEVICE_MANAGER_CONFIG_HPP_INCLUDED

#include <sge/x11input/create_parameters_fwd.hpp>
#include <sge/x11input/device/id.hpp>
#include <sge/x11input/device/manager/config_base.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/unique_ptr_fwd.hpp>
#include <fcppt/function/object.hpp>
#include <fcppt/signal/object_fwd.hpp>
#include <fcppt/config/external_begin.hpp>
#include <X11/extensions/XInput2.h>
#include <boost/ptr_container/ptr_map.hpp>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace x11input
{
namespace device
{
namespace manager
{

template<
	typename X11Object,
	typename DiscoverEvent,
	typename RemoveEvent
>
class config
:
	public device::manager::config_base
{
	FCPPT_NONCOPYABLE(
		config
	);
public:
	typedef fcppt::signal::object<
		void (DiscoverEvent const &)
	> discover_signal;

	typedef fcppt::signal::object<
		void (RemoveEvent const &)
	> remove_signal;

	typedef fcppt::unique_ptr<
		X11Object
	> object_unique_ptr;

	typedef fcppt::function::object<
		object_unique_ptr (
			x11input::create_parameters const &
		)
	> create_function;

	config(
		discover_signal &,
		remove_signal &,
		create_function const &
	);

	~config();

	void
	initial(
		x11input::create_parameters const &
	);

	void
	add(
		x11input::create_parameters const &
	);

	void
	remove(
		x11input::device::id
	);

	void
	dispatch_initial();
private:
	typedef boost::ptr_map<
		sge::x11input::device::id,
		X11Object
	> object_map;

	X11Object &
	insert_into_map(
		object_map &,
		x11input::create_parameters const &
	);

	object_map objects_;

	object_map initial_objects_;

	discover_signal &discover_;

	remove_signal &remove_;

	create_function const create_;
};

}
}
}
}

#endif
