/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2015 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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
#include <sge/input/keyboard/char_repeated.hpp>
#include <sge/input/keyboard/key.hpp>
#include <sge/input/keyboard/key_code.hpp>
#include <sge/input/keyboard/key_id.hpp>
#include <sge/input/keyboard/key_event.hpp>
#include <sge/input/keyboard/key_repeat_event.hpp>
#include <sge/input/keyboard/modifier.hpp>
#include <sge/timer/basic_impl.hpp>
#include <sge/timer/reset_when_expired.hpp>
#include <fcppt/const.hpp>
#include <fcppt/from_optional.hpp>
#include <fcppt/maybe_void.hpp>
#include <fcppt/optional_comparison.hpp>
#include <fcppt/optional_impl.hpp>
#include <fcppt/string.hpp>
#include <fcppt/strong_typedef_construct_cast.hpp>
#include <fcppt/text.hpp>
#include <fcppt/cast/size_fun.hpp>
#include <fcppt/container/find_opt_mapped.hpp>
#include <fcppt/container/raw_vector_impl.hpp>
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
	old_key_(),
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

	sge::input::keyboard::key_pressed const key_value{
		sge::dinput::is_down(
			_data.dwData
		)
	};

	sge::input::keyboard::key const key{
		fcppt::from_optional(
			fcppt::container::find_opt_mapped(
				info_.key_map(),
				offset
			),
			fcppt::const_(
				sge::input::keyboard::key_code::unknown
			)
		),
		fcppt::strong_typedef_construct_cast<
			sge::input::keyboard::key_id,
			fcppt::cast::size_fun
		>(
			offset
		)
	};

	key_signal_(
		sge::input::keyboard::key_event(
			key,
			key_value
		)
	);

	fcppt::maybe_void(
		sge::dinput::keyboard::map_virtual_key(
			offset,
			kblayout_
		),
		[
			&_data,
			offset,
			key_value,
			this
		](
			UINT const _virtual_code
		)
		{
			if(
				_virtual_code
				<
				states_.size()
			)
				states_[
					_virtual_code
				] =
					static_cast<
						BYTE
					>(
						_data.dwOfs
					);

			if(
				!key_value.get()
			)
				return;

			sge::dinput::keyboard::char_vector const chars(
				sge::dinput::keyboard::keycode_to_chars(
					_virtual_code,
					offset,
					states_,
					kblayout_
				)
			);

			for(
				auto const elem
				:
				chars
			)
				char_signal_(
					sge::input::keyboard::char_event(
						elem,
						sge::input::keyboard::char_repeated{
							false
						}
					)
				);
		}
	);

	if(
		!key_value.get()
	)
	{
		old_key_ =
			optional_key();

		repeat_time_.reset();
	}
	else if(
		old_key_
		!=
		optional_key(
			key
		)
	)
	{
		repeat_time_.reset();

		old_key_ =
			optional_key(
				key
			);
	}

	fcppt::maybe_void(
		old_key_,
		[
			this
		](
			sge::input::keyboard::key const &_old_key
		)
		{
			if(
				sge::timer::reset_when_expired(
					repeat_time_
				)
			)
				key_repeat_signal_(
					sge::input::keyboard::key_repeat_event(
						_old_key
					)
				);
		}
	);
}
