/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2010 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#include "../keyboard.hpp"
#include "../keyboard_repeat.hpp"
#include <sge/input/keyboard/key.hpp>
#include <sge/input/keyboard/key_code.hpp>
#include <sge/input/keyboard/key_event.hpp>
#include <sge/input/keyboard/key_repeat_event.hpp>
#include <sge/input/exception.hpp>
#include <fcppt/chrono/duration_impl.hpp>
#include <fcppt/container/array.hpp>
#include <fcppt/container/bitfield/basic_impl.hpp>
#include <fcppt/signal/object_impl.hpp>
#include <fcppt/optional_impl.hpp>
#include <fcppt/string.hpp>
#include <fcppt/text.hpp>

sge::dinput::keyboard::keyboard(
	dinput::device_parameters const &_parameters,
	dinput::key_converter const &_conv
)
:
	sge::input::keyboard::device(),
	dinput::device(
		_parameters
	),
	modifiers_(
		sge::input::keyboard::mod_state::null()
	),
	conv_(_conv),
	kblayout_(
		::GetKeyboardLayout(
			0
		)
	),
	key_signal_(),
	key_repeat_signal_(),
	repeat_time_(
		dinput::keyboard_repeat(),
		sge::time::activation_state::active
	),
	old_key_(),
	keys_()
{
	this->set_data_format(
		&c_dfDIKeyboard
	);

	this->enum_objects(
		enum_keyboard_keys
	);

	acquire();
}

fcppt::signal::auto_connection
sge::dinput::keyboard::key_callback(
	sge::input::keyboard::key_callback const &_callback
)
{
	return
		key_signal_.connect(
			_callback
		);
}

fcppt::signal::auto_connection
sge::dinput::keyboard::key_repeat_callback(
	sge::input::keyboard::key_repeat_callback const &_callback
)
{
	return
		key_repeat_signal_.connect(
			_callback
		);
}

sge::input::keyboard::mod_state const
sge::dinput::keyboard::mod_state() const
{
	return modifiers_;
}

void
sge::dinput::keyboard::dispatch()
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
			(offset & 0x80)
			!= 0
		);

		switch(
			offset
		)
		{
		case VK_CONTROL:
			modifiers_.set(
				sge::input::keyboard::modifiers::ctrl,
				key_value
			);
			break;
		case VK_MENU:
			modifiers_set(
				sge::input::keyboard::modifiers::alt,
				key_value
			);
			break;
		case VK_SHIFT:
			modifiers_.set(
				sge::input::keyboard::modifiers::shift,
				key_value
			);
			break;
		}

		input::keyboard::key_code::type const key_code(
			keys_[
				offset
			]
		);

		input::keyboard::key const key(
			key_code,
			dinput::keycode_to_char(
				key_code,
				conv_,
				kblayout_
			)
		)

		key_signal_(
			input::keyboard::key_event(
				key,
				key_value
			)
		);

		if(
			!key_value
		)
		{
			old_key.reset();

			repeat_time_.reset();
		}
		else if(
			!old_key_
			|| *old_key_ != key_code
		)
		{
			repeat_time.reset();

			old_key_ = key_code;
		}
	}

	if(
		old_key_
		&&
		repeat_time_.update_b()
	)
		key_repeat_signal_(
			sge::input::keyboard::key_repeat_event(
				key
			)
		);
}

BOOL
sge::dinput::keyboard::enum_keyboard_keys(
	LPCDIDEVICEOBJECTINSTANCE _ddoi,
	LPVOID _state
)
{
	dinput::keyboard &instance(
		*static_cast<
			dinput::keyboard *
		>(
			_state
		)
	);

	fcppt::string const key_name(
		_ddoi->tszName
	);

	instance.keys_[
		_ddoi->dwOfs
	] =
		input::keyboard::key(
			//k.name() + key_name,
			instance.conv_.create_key_code(
				_ddoi->dwOfs
			),
			key_name.size() == 1
			?
				key_name[0]
			:
				0
			)
		);

	return DIENUM_CONTINUE;
}
