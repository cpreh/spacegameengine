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


#include <sge/x11input/create_parameters.hpp>
#include <sge/x11input/mask_c.hpp>
#include <sge/x11input/device/id.hpp>
#include <sge/x11input/device/use.hpp>
#include <sge/x11input/device/info/single.hpp>
#include <sge/x11input/device/manager/config_base.hpp>
#include <sge/x11input/device/manager/config_map.hpp>
#include <sge/x11input/device/manager/object.hpp>
#include <awl/backends/x11/discard.hpp>
#include <awl/backends/x11/display_fwd.hpp>
#include <awl/backends/x11/sync.hpp>
#include <fcppt/reference_impl.hpp>
#include <fcppt/strong_typedef_output.hpp>
#include <fcppt/text.hpp>
#include <fcppt/algorithm/fold.hpp>
#include <fcppt/assert/error.hpp>
#include <fcppt/bit/test.hpp>
#include <fcppt/container/find_opt_iterator.hpp>
#include <fcppt/log/_.hpp>
#include <fcppt/log/debug.hpp>
#include <fcppt/log/object_fwd.hpp>
#include <fcppt/optional/maybe.hpp>
#include <fcppt/optional/maybe_void.hpp>
#include <fcppt/config/external_begin.hpp>
#include <X11/extensions/XInput2.h>
#include <boost/range/iterator_range_core.hpp>
#include <functional>
#include <utility>
#include <fcppt/config/external_end.hpp>


sge::x11input::device::manager::object::object(
	fcppt::log::object &_log,
	awl::backends::x11::display &_display,
	sge::x11input::device::manager::config_map &&_config
)
:
	log_{
		_log
	},
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
		fcppt::bit::test(
			_info.flags,
			sge::x11input::mask_c<
				XIMasterAdded
			>()
		)
		||
		fcppt::bit::test(
			_info.flags,
			sge::x11input::mask_c<
				XIDeviceEnabled
			>()
		)
	)
	{
		sge::x11input::device::use const device_use(
			_info.use
		);

		FCPPT_LOG_DEBUG(
			log_,
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

		fcppt::optional::maybe(
			device_info.get(),
			[
				this,
				device_id
			]{
				FCPPT_LOG_DEBUG(
					log_,
					fcppt::log::_
						<< FCPPT_TEXT("x11input: Device with id: ")
						<< device_id
						<< FCPPT_TEXT(" seems to have already disappeared.")
				);
			},
			[
				device_id,
				device_use,
				this
			](
				fcppt::reference<
					XIDeviceInfo const
				> const _device_info
			)
			{
				if(
					this->update(
						device_use,
						std::bind(
							&sge::x11input::device::manager::config_base::add,
							std::placeholders::_1,
							sge::x11input::create_parameters(
								_device_info.get()
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
		);
	}

	if(
		fcppt::bit::test(
			_info.flags,
			sge::x11input::mask_c<
				XIMasterRemoved
			>()
		)
		||
		fcppt::bit::test(
			_info.flags,
			sge::x11input::mask_c<
				XISlaveRemoved
			>()
		)
	)
	{
		FCPPT_LOG_DEBUG(
			log_,
			fcppt::log::_
				<< FCPPT_TEXT("x11input: Removed device with id: ")
				<< device_id
		);

		fcppt::optional::maybe_void(
			fcppt::container::find_opt_iterator(
				uses_,
				device_id
			),
			[
				device_id,
				this
			](
				use_map::iterator const _it
			)
			{
				this->update(
					_it->second,
					std::bind(
						&sge::x11input::device::manager::config_base::remove,
						std::placeholders::_1,
						device_id
					)
				);

				uses_.erase(
					_it
				);
			}
		);
	}

	awl::backends::x11::sync(
		display_,
		awl::backends::x11::discard(
			false
		)
	);
}

void
sge::x11input::device::manager::object::dispatch_initial()
{
	for(
		auto const &item
		:
		config_
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
	auto const range(
		config_.equal_range(
			_use
		)
	);

	return
		fcppt::algorithm::fold(
			boost::make_iterator_range(
				range.first,
				range.second
			),
			false,
			[
				&_function
			](
				sge::x11input::device::manager::config_map::value_type const &_value,
				bool const _state
			)
			{
				return
					_function(
						*_value.second
					)
					||
					_state;
			}
		);
}
