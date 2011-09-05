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


#include <sge/input/mouse/collector.hpp>
#include <sge/input/mouse/device.hpp>
#include <sge/input/processor.hpp>
#include <fcppt/assign/make_container.hpp>
#include <fcppt/container/ptr/insert_unique_ptr_map.hpp>
#include <fcppt/preprocessor/disable_vc_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>
#include <fcppt/signal/connection_manager.hpp>
#include <fcppt/signal/shared_connection.hpp>
#include <fcppt/tr1/functional.hpp>
#include <fcppt/make_unique_ptr.hpp>

FCPPT_PP_PUSH_WARNING
FCPPT_PP_DISABLE_VC_WARNING(4355)
sge::input::mouse::collector::collector(
	input::processor_ptr const _processor
)
:
	connections_(
		fcppt::assign::make_container<
			fcppt::signal::connection_manager::container
		>(
			fcppt::signal::shared_connection(
				_processor->mouse_discover_callback(
					std::tr1::bind(
						&collector::discover_callback,
						this,
						std::tr1::placeholders::_1
					)
				)
			)
		)
		(
			fcppt::signal::shared_connection(
				_processor->mouse_remove_callback(
					std::tr1::bind(
						&collector::remove_callback,
						this,
						std::tr1::placeholders::_1
					)
				)
			)
		)
	),
	axis_signal_(),
	button_signal_(),
	devices_()
{
	mouse::device_vector const devices(
		_processor->mice()
	);

	for(
		mouse::device_vector::const_iterator it(
			devices.begin()
		);
		it != devices.end();
		++it
	)
		discover_callback(
			*it
		);
}
FCPPT_PP_POP_WARNING

sge::input::mouse::collector::~collector()
{
}

fcppt::signal::auto_connection
sge::input::mouse::collector::axis_callback(
	mouse::axis_callback const &_callback
)
{
	return
		axis_signal_.connect(
			_callback
		);
}

fcppt::signal::auto_connection
sge::input::mouse::collector::button_callback(
	mouse::button_callback const &_callback
)
{
	return
		button_signal_.connect(
			_callback
		);
}

void
sge::input::mouse::collector::axis_callback_internal(
	mouse::axis_event const &_event
)
{
	axis_signal_(
		_event
	);
}

void
sge::input::mouse::collector::button_callback_internal(
	mouse::button_event const &_event
)
{
	button_signal_(
		_event
	);
}

void
sge::input::mouse::collector::discover_callback(
	mouse::device_ptr const _device
)
{
	fcppt::container::ptr::insert_unique_ptr_map(
		devices_,
		_device,
		fcppt::make_unique_ptr<
			fcppt::signal::connection_manager
		>(
			fcppt::assign::make_container<
				fcppt::signal::connection_manager::container
			>(
				fcppt::signal::shared_connection(
					_device->axis_callback(
						std::tr1::bind(
							&collector::axis_callback_internal,
							this,
							std::tr1::placeholders::_1
						)
					)
				)
			)
			(
				fcppt::signal::shared_connection(
					_device->button_callback(
						std::tr1::bind(
							&collector::button_callback_internal,
							this,
							std::tr1::placeholders::_1
						)
					)
				)
			)
		)
	);
}

void
sge::input::mouse::collector::remove_callback(
	mouse::device_ptr const _device
)
{
	devices_.erase(
		_device
	);
}
