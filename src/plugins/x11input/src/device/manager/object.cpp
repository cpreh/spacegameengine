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


#include <sge/x11input/device/manager/object.hpp>
#include <sge/x11input/device/manager/config_base.hpp>
#include <sge/x11input/device/manager/config_map.hpp>
#include <sge/x11input/device/info/single.hpp>
#include <sge/x11input/device/id.hpp>
#include <sge/x11input/device/use.hpp>
#include <sge/x11input/create_parameters.hpp>
#include <awl/backends/x11/display_fwd.hpp>
#include <fcppt/tr1/functional.hpp>
#include <fcppt/config/external_begin.hpp>
#include <utility>
#include <X11/extensions/XInput2.h>
#include <fcppt/config/external_end.hpp>

sge::x11input::device::manager::object::object(
	awl::backends::x11::display &_display,
	device::manager::config_map const &_config
)
:
	display_(_display),
	config_(_config)
{
}

sge::x11input::device::manager::object::~object()
{
}

void
sge::x11input::device::manager::object::initial(
	XIDeviceInfo const &_info
)
{
	this->update(
		x11input::device::use(
			_info.use
		),
		std::tr1::bind(
			&x11input::device::manager::config_base::initial,
			std::tr1::placeholders::_1,
			x11input::create_parameters(
				x11input::device::id(
					_info.deviceid
				),
				_info
			)
		)
	);
}

void
sge::x11input::device::manager::object::change(
	XIHierarchyInfo const &_info
)
{
	x11input::device::id const device_id(
		_info.deviceid
	);

	x11input::device::use const device_use(
		_info.use
	);

	x11input::device::info::single const device_info(
		display_,
		device_id
	);

	if(
		(_info.flags & XIMasterAdded)
		|| (_info.flags & XISlaveAdded)
	)
		this->update(
			device_use,
			std::tr1::bind(
				&x11input::device::manager::config_base::add,
				std::tr1::placeholders::_1,
				x11input::create_parameters(
					device_id,
					device_info.get()
				)
			)
		);

	if(
		(_info.flags & XIMasterRemoved)
		|| (_info.flags & XISlaveRemoved)
	)
		this->update(
			device_use,
			std::tr1::bind(
				&x11input::device::manager::config_base::remove,
				std::tr1::placeholders::_1,
				device_id
			)
		);
}

template<
	typename Function
>
void
sge::x11input::device::manager::object::update(
	x11input::device::use const _use,
	Function const &_function
)
{
	typedef std::pair<
		device::manager::config_map::const_iterator,
		device::manager::config_map::const_iterator
	> range_pair;

	range_pair const range(
		config_.equal_range(
			_use
		)
	);

	for(
		device::manager::config_map::const_iterator it(
			range.first
		);
		it != range.second;
		++it
	)
		_function(
			*it->second
		);
}
