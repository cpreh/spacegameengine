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


#include <sge/input/keyboard/collector.hpp>
#include <sge/input/keyboard/device.hpp>
#include <sge/input/processor.hpp>
#include <fcppt/assign/make_container.hpp>
#include <fcppt/container/bitfield/basic_impl.hpp>
#include <fcppt/container/ptr/insert_unique_ptr_map.hpp>
#include <fcppt/signal/connection_manager.hpp>
#include <fcppt/signal/shared_connection.hpp>
#include <fcppt/tr1/functional.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <boost/foreach.hpp>

sge::input::keyboard::collector::collector(
	input::processor_ptr const _processor
)
:
	connections_(
		fcppt::assign::make_container<
			fcppt::signal::connection_manager::container
		>(
			fcppt::signal::shared_connection(
				_processor->keyboard_discover_callback(
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
				_processor->keyboard_remove_callback(
					std::tr1::bind(
						&collector::remove_callback,
						this,
						std::tr1::placeholders::_1
					)
				)
			)
		)
	),
	signal_(),
	repeat_signal_(),
	char_signal_(),
	devices_()
{
	BOOST_FOREACH(
		keyboard::device_vector::value_type cur_device,
		_processor->keyboards()
	)
		this->discover_callback(
			cur_device
		);
}

sge::input::keyboard::collector::~collector()
{
}

fcppt::signal::auto_connection
sge::input::keyboard::collector::key_callback(
	keyboard::key_callback const &_callback
)
{
	return
		signal_.connect(
			_callback
		);
}

fcppt::signal::auto_connection
sge::input::keyboard::collector::key_repeat_callback(
	keyboard::key_repeat_callback const &_callback
)
{
	return
		repeat_signal_.connect(
			_callback
		);
}

fcppt::signal::auto_connection
sge::input::keyboard::collector::char_callback(
	keyboard::char_callback const &_callback
)
{
	return
		char_signal_.connect(
			_callback
		);
}

sge::input::keyboard::mod_state const
sge::input::keyboard::collector::mod_state() const
{
	keyboard::mod_state ret(
		keyboard::mod_state::null()
	);

	for(
		keyboard_map::const_iterator it(
			devices_.begin()
		);
		it != devices_.end();
		++it
	)
		ret |= it->first->mod_state();
	
	return ret;
}

void
sge::input::keyboard::collector::key_callback_internal(
	keyboard::key_event const &_event
)
{
	signal_(
		_event
	);
}

void
sge::input::keyboard::collector::key_repeat_callback_internal(
	keyboard::key_repeat_event const &_event
)
{
	repeat_signal_(
		_event
	);
}

void
sge::input::keyboard::collector::char_callback_internal(
	keyboard::char_event const &_event
)
{
	char_signal_(
		_event
	);
}

void
sge::input::keyboard::collector::discover_callback(
	keyboard::device_ptr const _device
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
					_device->key_callback(
						std::tr1::bind(
							&collector::key_callback_internal,
							this,
							std::tr1::placeholders::_1
						)
					)
				)
			)
			(
				fcppt::signal::shared_connection(
					_device->key_repeat_callback(
						std::tr1::bind(
							&collector::key_repeat_callback_internal,
							this,
							std::tr1::placeholders::_1
						)
					)
				)
			)
			(
				fcppt::signal::shared_connection(
					_device->char_callback(
						std::tr1::bind(
							&collector::char_callback_internal,
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
sge::input::keyboard::collector::remove_callback(
	keyboard::device_ptr const _device
)
{
	devices_.erase(
		_device
	);
}
