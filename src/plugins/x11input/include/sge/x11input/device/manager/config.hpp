/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2011 Carl Philipp Reh (sefi@s-e-f-i.de)

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
#include <fcppt/function/object.hpp>
#include <fcppt/signal/object_fwd.hpp>
#include <fcppt/config/external_begin.hpp>
#include <X11/extensions/XInput2.h>
#include <vector>
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
	typename X11ObjectPtr,
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
	typedef std::vector<
		X11ObjectPtr
	> object_vector;

	typedef fcppt::signal::object<
		void (DiscoverEvent const &)
	> discover_signal;

	typedef fcppt::signal::object<
		void (RemoveEvent const &)
	> remove_signal;

	typedef fcppt::function::object<
		X11ObjectPtr const (
			x11input::create_parameters const &
		)
	> create_function;

	config(
		object_vector &,
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
private:
	object_vector &objects_;

	discover_signal &discover_;

	remove_signal &remove_;

	create_function const create_;
};

}
}
}
}

#endif
