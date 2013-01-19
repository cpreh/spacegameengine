/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2013 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#include <sge/input/logger.hpp>
#include <sge/x11input/create_parameters.hpp>
#include <sge/x11input/device/id.hpp>
#include <sge/x11input/device/use.hpp>
#include <sge/x11input/device/info/single.hpp>
#include <sge/x11input/device/manager/config_base.hpp>
#include <sge/x11input/device/manager/config_map.hpp>
#include <sge/x11input/device/manager/object.hpp>
#include <awl/backends/x11/discard.hpp>
#include <awl/backends/x11/display.hpp>
#include <fcppt/text.hpp>
#include <fcppt/assert/error.hpp>
#include <fcppt/log/debug.hpp>
#include <fcppt/log/output.hpp>
#include <fcppt/config/external_begin.hpp>
#include <X11/extensions/XInput2.h>
#include <functional>
#include <utility>
#include <fcppt/config/external_end.hpp>


sge::x11input::device::manager::object::object(
	awl::backends::x11::display &_display,
	sge::x11input::device::manager::config_map &&_config
)
:
	display_(
		_display
	),
	config_(
		std::move(
			_config
		)
	),
	uses_()
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
		sge::x11input::device::use(
			_info.use
		),
		std::bind(
			&sge::x11input::device::manager::config_base::initial,
			std::placeholders::_1,
			sge::x11input::create_parameters(
				sge::x11input::device::id(
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
	sge::x11input::device::id const device_id(
		_info.deviceid
	);

	if(
		(
			(_info.flags & XIMasterAdded)
			||
			(_info.flags & XIDeviceEnabled)
		)
	)
	{
		sge::x11input::device::use const device_use(
			_info.use
		);

		FCPPT_LOG_DEBUG(
			sge::input::logger(),
			fcppt::log::_
				<< FCPPT_TEXT("x11input: Discovered device with id: ")
				<< device_id
				<< FCPPT_TEXT(" and use: ")
				<< device_use
		);

		sge::x11input::device::info::single const device_info(
			display_,
			device_id
		);

		if(
			device_info.get()
			==
			nullptr
		)
		{
			FCPPT_LOG_DEBUG(
				sge::input::logger(),
				fcppt::log::_
					<< FCPPT_TEXT("x11input: Device with id: ")
					<< device_id
					<< FCPPT_TEXT(" seems to have already disappeared.")
			);

			return;
		}

		if(
			this->update(
				device_use,
				std::bind(
					&sge::x11input::device::manager::config_base::add,
					std::placeholders::_1,
					sge::x11input::create_parameters(
						device_id,
						*device_info.get()
					)
				)
			)
		)
		{
			FCPPT_ASSERT_ERROR(
				uses_.insert(
					std::make_pair(
						device_id,
						device_use
					)
				).second
			);
		}
	}

	if(
		(_info.flags & XIMasterRemoved)
		|| (_info.flags & XISlaveRemoved)
	)
	{
		FCPPT_LOG_DEBUG(
			sge::input::logger(),
			fcppt::log::_
				<< FCPPT_TEXT("x11input: Removed device with id: ")
				<< device_id
		);

		use_map::iterator const it(
			uses_.find(
				device_id
			)
		);

		// It is possible we had no use for this device
		if(
			it == uses_.end()
		)
			return;

		this->update(
			it->second,
			std::bind(
				&sge::x11input::device::manager::config_base::remove,
				std::placeholders::_1,
				device_id
			)
		);

		uses_.erase(
			it
		);
	}

	display_.sync(
		awl::backends::x11::discard(
			false
		)
	);
}

void
sge::x11input::device::manager::object::dispatch_initial()
{
	for(
		auto const &item : config_
	)
		item.second->dispatch_initial();
}

template<
	typename Function
>
bool
sge::x11input::device::manager::object::update(
	sge::x11input::device::use const _use,
	Function const &_function
)
{
	typedef std::pair<
		sge::x11input::device::manager::config_map::const_iterator,
		sge::x11input::device::manager::config_map::const_iterator
	> range_pair;

	range_pair const range(
		config_.equal_range(
			_use
		)
	);

	bool changed(
		false
	);

	for(
		sge::x11input::device::manager::config_map::const_iterator it(
			range.first
		);
		it != range.second;
		++it
	)
		changed =
			_function(
				*it->second
			)
			|| changed;

	return changed;
}
