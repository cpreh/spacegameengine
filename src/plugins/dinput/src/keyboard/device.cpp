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


#include <sge/dinput/has_cursor.hpp>
#include <sge/dinput/has_focus.hpp>
#include <sge/dinput/is_down.hpp>
#include <sge/dinput/keyboard/device.hpp>
#include <sge/dinput/keyboard/key_map.hpp>
#include <sge/dinput/keyboard/keycode_to_chars.hpp>
#include <sge/dinput/keyboard/make_info.hpp>
#include <sge/dinput/keyboard/map_virtual_key.hpp>
#include <sge/dinput/keyboard/repeat.hpp>
#include <sge/input/exception.hpp>
#include <sge/input/keyboard/char_event.hpp>
#include <sge/input/keyboard/key_code.hpp>
#include <sge/input/keyboard/key_event.hpp>
#include <sge/input/keyboard/key_repeat_event.hpp>
#include <sge/input/keyboard/modifier.hpp>
#include <sge/timer/basic_impl.hpp>
#include <sge/timer/reset_when_expired.hpp>
#include <fcppt/string.hpp>
#include <fcppt/text.hpp>
#include <fcppt/container/raw_vector_impl.hpp>
#include <fcppt/container/bitfield/object_impl.hpp>
#include <fcppt/preprocessor/disable_vc_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>
#include <fcppt/signal/object_impl.hpp>
#include <fcppt/config/external_begin.hpp>
#include <algorithm>
#include <fcppt/config/external_end.hpp>


FCPPT_PP_PUSH_WARNING
FCPPT_PP_DISABLE_VC_WARNING(4355)

sge::dinput::keyboard::device::device(
	dinput::device::parameters const &_parameters
)
:
	sge::input::keyboard::device(),
	sge::dinput::device::object(
		_parameters,
		c_dfDIKeyboard
	),
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
			sge::dinput::keyboard::repeat()
		)
	),
	old_key_code_(),
	info_(
		sge::dinput::keyboard::make_info(
			this->get()
		)
	),
	states_()
{
	std::fill(
		states_.begin(),
		states_.end(),
		0
	);
}

FCPPT_PP_POP_WARNING

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
		sge::dinput::is_down(
			states_[
				VK_CONTROL
			]
		)
	)
		ret |= sge::input::keyboard::modifier::control;

	if(
		sge::dinput::is_down(
			states_[
				VK_MENU
			]
		)
	)
		ret |= sge::input::keyboard::modifier::alt;

	if(
		sge::dinput::is_down(
			states_[
				VK_SHIFT
			]
		)
	)
		ret |= sge::input::keyboard::modifier::shift;

	return ret;
}

bool
sge::dinput::keyboard::device::needs_acquire(
	sge::dinput::has_focus const _has_focus,
	sge::dinput::has_cursor
) const
{
	return
		_has_focus.get();
}

void
sge::dinput::keyboard::device::on_dispatch(
	DIDEVICEOBJECTDATA const &_data
)
{
	DWORD const offset(
		_data.dwOfs
	);

	bool const key_value(
		sge::dinput::is_down(
			_data.dwData
		)
	);

	sge::dinput::keyboard::key_map::const_iterator const it(
		info_.key_map().find(
			offset
		)
	);

	sge::input::keyboard::key_code const key_code(
		it
		==
		info_.key_map().end()
		?
			sge::input::keyboard::key_code::unknown
		:
			it->second
	);

	key_signal_(
		sge::input::keyboard::key_event(
			key_code,
			key_value
		)
	);

	sge::dinput::keyboard::optional_uint const virtual_code(
		sge::dinput::keyboard::map_virtual_key(
			offset,
			kblayout_
		)
	);

	if(
		virtual_code
		&&
		*virtual_code
		<
		states_.size()
	)
		states_[
			*virtual_code
		] =
			static_cast<
				BYTE
			>(
				_data.dwOfs
			);

	if(
		key_value
		&&
		virtual_code
	)
	{
		sge::dinput::keyboard::char_vector const &chars(
			sge::dinput::keyboard::keycode_to_chars(
				*virtual_code,
				offset,
				states_,
				kblayout_
			)
		);

		for(
			auto const elem : chars
		)
			char_signal_(
				sge::input::keyboard::char_event(
					elem,
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
