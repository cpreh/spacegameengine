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


#include "../manager.hpp"
#include "../id.hpp"
#include "../manager_config_base.hpp"
#include "../manager_config_map.hpp"
#include "../use.hpp"
#include <fcppt/config/external_begin.hpp>
#include <utility>
#include <X11/extensions/XInput2.h>
#include <fcppt/config/external_end.hpp>

sge::x11input::device::manager::manager(
	device::manager_config_map const &_config
)
:
	config_(_config)
{
}

sge::x11input::device::manager::~manager()
{
}

void
sge::x11input::device::manager::initial(
	XIDeviceInfo const &_info
)
{
	this->update(
		x11input::device::id(
			_info.deviceid
		),
		x11input::device::use(
			_info.use
		),
		&x11input::device::manager_config_base::initial
	);
}

void
sge::x11input::device::manager::change(
	XIHierarchyInfo const &_info
)
{
	x11input::device::id const device_id(
		_info.deviceid
	);

	x11input::device::use const device_use(
		_info.use
	);

	if(
		(_info.flags & XIMasterAdded)
		|| (_info.flags & XISlaveAdded)
	)
		this->update(
			device_id,
			device_use,
			&x11input::device::manager_config_base::add
		);

	if(
		(_info.flags & XIMasterRemoved)
		|| (_info.flags & XISlaveRemoved)
	)
		this->update(
			device_id,
			device_use,
			&x11input::device::manager_config_base::remove
		);
}

template<
	typename Function
>
void
sge::x11input::device::manager::update(
	x11input::device::id const _id,
	x11input::device::use const _use,
	Function const &_function
)
{
	typedef std::pair<
		device::manager_config_map::const_iterator,
		device::manager_config_map::const_iterator
	> range_pair;

	range_pair const range(
		config_.equal_range(
			_use
		)
	);

	for(
		device::manager_config_map::const_iterator it(
			range.first
		);
		it != range.second;
		++it
	)
		(
			(*it->second).*_function
		)
		(
			_id
		);
}
