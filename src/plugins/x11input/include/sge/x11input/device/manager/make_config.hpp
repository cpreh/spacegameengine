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


#ifndef SGE_X11INPUT_DEVICE_MANAGER_MAKE_CONFIG_HPP_INCLUDED
#define SGE_X11INPUT_DEVICE_MANAGER_MAKE_CONFIG_HPP_INCLUDED

#include <sge/x11input/device/manager/config.hpp>
#include <sge/x11input/device/manager/config_base_ptr.hpp>
#include <fcppt/make_shared_ptr.hpp>
#include <fcppt/ref.hpp>
#include <fcppt/signal/object_fwd.hpp>
#include <fcppt/config/external_begin.hpp>
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
	typename X11Object,
	typename DiscoverEvent,
	typename RemoveEvent,
	typename CreateFunction
>
device::manager::config_base_ptr const
make_config(
	fcppt::signal::object<
		void (DiscoverEvent const &)
	> &_discover,
	fcppt::signal::object<
		void (RemoveEvent const &)
	> &_remove,
	CreateFunction const &_create
)
{
	typedef device::manager::config<
		X11Object,
		DiscoverEvent,
		RemoveEvent
	> result_type;

	return
		fcppt::make_shared_ptr<
			result_type
		>(
			fcppt::ref(
				_discover
			),
			fcppt::ref(
				_remove
			),
			typename result_type::create_function(
				_create
			)
		);
}

}
}
}
}

#endif
