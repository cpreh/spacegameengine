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


#include <sge/input/keyboard/manager.hpp>
#include <sge/input/keyboard/char_callback.hpp>
#include <sge/input/keyboard/device.hpp>
#include <sge/input/keyboard/device_vector.hpp>
#include <sge/input/keyboard/discover_callback.hpp>
#include <sge/input/keyboard/discover_event.hpp>
#include <sge/input/keyboard/key_callback.hpp>
#include <sge/input/keyboard/key_repeat_callback.hpp>
#include <sge/input/keyboard/remove_callback.hpp>
#include <sge/input/keyboard/remove_event.hpp>
#include <sge/input/processor.hpp>
#include <fcppt/assert/error.hpp>
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
sge::input::keyboard::manager::manager(
	input::processor &_processor,
	input::keyboard::discover_callback const &_discover_callback,
	input::keyboard::remove_callback const &_remove_callback,
	input::keyboard::char_callback const &_char_callback,
	input::keyboard::key_callback const &_key_callback,
	input::keyboard::key_repeat_callback const &_key_repeat_callback
)
:
	devices_(),
	discover_callback_(
		_discover_callback
	),
	remove_callback_(
		_remove_callback
	),
	char_callback_(
		_char_callback
	),
	key_callback_(
		_key_callback
	),
	key_repeat_callback_(
		_key_repeat_callback
	),
	connections_(
		fcppt::assign::make_container<
			fcppt::signal::connection_manager::container
		>(
			fcppt::signal::shared_connection(
				_processor.keyboard_discover_callback(
					std::tr1::bind(
						&keyboard::manager::discover,
						this,
						std::tr1::placeholders::_1
					)
				)
			)
		)
		(
			fcppt::signal::shared_connection(
				_processor.keyboard_remove_callback(
					std::tr1::bind(
						&keyboard::manager::remove,
						this,
						std::tr1::placeholders::_1
					)
				)
			)
		)
	)
{
	keyboard::device_vector const current_devices(
		_processor.keyboards()
	);

	for(
		keyboard::device_vector::const_iterator it(
			current_devices.begin()
		);
		it != current_devices.end();
		++it
	)
		this->discover(
			input::keyboard::discover_event(
				*it
			)
		);
}
FCPPT_PP_POP_WARNING

sge::input::keyboard::manager::~manager()
{
}

sge::input::keyboard::manager::keyboard_map const &
sge::input::keyboard::manager::devices() const
{
	return devices_;
}

void
sge::input::keyboard::manager::discover(
	input::keyboard::discover_event const &_event
)
{
	FCPPT_ASSERT_ERROR(
		fcppt::container::ptr::insert_unique_ptr_map(
			devices_,
			_event.device(),
			fcppt::make_unique_ptr<
				fcppt::signal::connection_manager
			>(
				fcppt::assign::make_container<
					fcppt::signal::connection_manager::container
				>(
					fcppt::signal::shared_connection(
						_event.device()->char_callback(
							char_callback_
						)
					)
				)
				(
					fcppt::signal::shared_connection(
						_event.device()->key_callback(
							key_callback_
						)
					)
				)
				(
					fcppt::signal::shared_connection(
						_event.device()->key_repeat_callback(
							key_repeat_callback_
						)
					)
				)
			)
		).second
		== true
	);

	if(
		discover_callback_
	)
		discover_callback_(
			_event
		);
}

void
sge::input::keyboard::manager::remove(
	input::keyboard::remove_event const &_event
)
{
	FCPPT_ASSERT_ERROR(
		devices_.erase(
			_event.device()
		)
		== 1u
	);

	if(
		remove_callback_
	)
		remove_callback_(
			_event
		);
}
