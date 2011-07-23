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


#include "../device.hpp"
#include "../key_converter.hpp"
#include "../key_is_down.hpp"
#include "../keycode_to_chars.hpp"
#include "../map_virtual_key.hpp"
#include "../repeat.hpp"
#include <sge/input/keyboard/char_event.hpp>
#include <sge/input/keyboard/key_code.hpp>
#include <sge/input/keyboard/key_event.hpp>
#include <sge/input/keyboard/key_repeat_event.hpp>
#include <sge/input/keyboard/modifier.hpp>
#include <sge/input/exception.hpp>
#include <sge/timer/basic_impl.hpp>
#include <sge/timer/reset_when_expired.hpp>
#include <fcppt/chrono/duration_impl.hpp>
#include <fcppt/container/array.hpp>
#include <fcppt/container/bitfield/basic_impl.hpp>
#include <fcppt/container/raw_vector_impl.hpp>
#include <fcppt/signal/object_impl.hpp>
#include <fcppt/optional_impl.hpp>
#include <fcppt/string.hpp>
#include <fcppt/text.hpp>
#include <algorithm>

sge::dinput::keyboard::device::device(
	dinput::device::parameters const &_parameters,
	dinput::keyboard::key_converter const &_conv
)
:
	sge::input::keyboard::device(),
	dinput::device::object(
		_parameters
	),
	conv_(_conv),
	kblayout_(
		::GetKeyboardLayout(
			0
		)
	),
	key_signal_(),
	key_repeat_signal_(),
	char_signal_(),
	repeat_time_(
		repeat_timer::parameters(
			dinput::keyboard::repeat()
		)
	),
	old_key_code_(),
	keys_(),
	states_()
{
	std::fill(
		states_.begin(),
		states_.end(),
		0
	);

	this->set_data_format(
		&c_dfDIKeyboard
	);

	this->enum_objects(
		enum_keyboard_keys
	);
}

sge::dinput::keyboard::device::~device()
{
}

fcppt::signal::auto_connection
sge::dinput::keyboard::device::key_callback(
	sge::input::keyboard::key_callback const &_callback
)
{
	return
		key_signal_.connect(
			_callback
		);
}

fcppt::signal::auto_connection
sge::dinput::keyboard::device::key_repeat_callback(
	sge::input::keyboard::key_repeat_callback const &_callback
)
{
	return
		key_repeat_signal_.connect(
			_callback
		);
}

fcppt::signal::auto_connection
sge::dinput::keyboard::device::char_callback(
	sge::input::keyboard::char_callback const &_callback
)
{
	return
		char_signal_.connect(
			_callback
		);
}

sge::input::keyboard::mod_state const
sge::dinput::keyboard::device::mod_state() const
{
	sge::input::keyboard::mod_state ret(
		sge::input::keyboard::mod_state::null()
	);

	if(
		dinput::keyboard::key_is_down(
			states_[
				VK_CONTROL
			]
		)
	)
		ret |= sge::input::keyboard::modifier::ctrl;
	
	if(
		dinput::keyboard::key_is_down(
			states_[
				VK_MENU
			]
		)
	)
		ret |= sge::input::keyboard::modifier::alt;

	if(
		dinput::keyboard::key_is_down(
			states_[
				VK_SHIFT
			]
		)
	)
		ret |= sge::input::keyboard::modifier::shift;

	return ret;
}

void
sge::dinput::keyboard::device::dispatch()
{
	input_buffer data;

	DWORD elements;

	if(
		!this->get_input(
			data,
			elements
		)
	)
		return;

	for(
		unsigned index = 0;
		index < elements;
		++index
	)
	{
		DWORD const offset(
			data[index].dwOfs
		);

		bool const key_value(
			dinput::keyboard::key_is_down(
				static_cast<
					BYTE
				>(
					data[
						index
					].dwData
				)
			)
		);

		input::keyboard::key_code::type const key_code(
			keys_[
				offset
			]
		);

		key_signal_(
			input::keyboard::key_event(
				key_code,
				key_value
			)
		);

		
		dinput::keyboard::optional_uint const virtual_code(
			dinput::keyboard::map_virtual_key(
				offset,
				kblayout_
			)
		);

		if(
			virtual_code
			&& *virtual_code < states_.size()
		)
			states_[
				*virtual_code
			] =
				key_value
				?
					0x80
				:
					0;

		if(
			key_value
			&& virtual_code
		)
		{
			sge::dinput::keyboard::char_vector const &chars(
				dinput::keyboard::keycode_to_chars(
					*virtual_code,
					offset,
					states_,
					kblayout_
				)
			);

			for(
				sge::dinput::keyboard::char_vector::const_iterator it(
					chars.begin()
				);
				it != chars.end();
				++it
			)
				char_signal_(
					sge::input::keyboard::char_event(
						*it,
						false
					)
				);
		}

		if(
			!key_value
		)
		{
			old_key_code_.reset();

			repeat_time_.reset();
		}
		else if(
			!old_key_code_
			|| *old_key_code_ != key_code
		)
		{
			repeat_time_.reset();

			old_key_code_ = key_code;
		}
	}

	if(
		old_key_code_
		&&
		sge::timer::reset_when_expired(
			repeat_time_
		)
	)
		key_repeat_signal_(
			sge::input::keyboard::key_repeat_event(
				*old_key_code_
			)
		);
}

BOOL
sge::dinput::keyboard::device::enum_keyboard_keys(
	LPCDIDEVICEOBJECTINSTANCE _ddoi,
	LPVOID _state
)
{
	dinput::keyboard::device &instance(
		dynamic_cast<
			dinput::keyboard::device &
		>(
			*static_cast<
				dinput::device::object *
			>(
				_state
			)
		)
	);

	instance.keys_[
		_ddoi->dwOfs
	] =
		instance.conv_.create_key_code(
			_ddoi->dwOfs
		);

	return DIENUM_CONTINUE;
}
