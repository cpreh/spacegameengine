/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2015 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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
#include <fcppt/optional_fwd.hpp>
#include <fcppt/strong_typedef_std_hash.hpp>
#include <fcppt/unique_ptr_impl.hpp>
#include <fcppt/signal/object_fwd.hpp>
#include <fcppt/config/external_begin.hpp>
#include <X11/extensions/XInput2.h>
#include <functional>
#include <unordered_map>
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
	public sge::x11input::device::manager::config_base
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

	typedef std::function<
		object_unique_ptr (
			sge::x11input::create_parameters const &
		)
	> create_function;

	config(
		discover_signal &,
		remove_signal &,
		create_function const &
	);

	~config()
	override;

	bool
	initial(
		sge::x11input::create_parameters const &
	)
	override;

	bool
	add(
		sge::x11input::create_parameters const &
	)
	override;

	bool
	remove(
		sge::x11input::device::id
	)
	override;

	void
	dispatch_initial()
	override;
private:
	typedef
	std::unordered_map<
		sge::x11input::device::id,
		object_unique_ptr
	>
	object_map;

	typedef
	fcppt::optional<
		X11Object &
	>
	optional_object_ref;

	optional_object_ref
	insert_into_map(
		object_map &,
		sge::x11input::create_parameters const &
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
