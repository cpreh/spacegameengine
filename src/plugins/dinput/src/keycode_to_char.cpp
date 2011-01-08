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

#include "../keycode_to_char.hpp"
#include "../key_converter.hpp"
#include "../di.hpp"
#include <sge/input/exception.hpp>
#include <sge/log/global.hpp>
#include <fcppt/container/array.hpp>
#include <fcppt/container/bitfield/basic_impl.hpp>
#include <fcppt/log/output.hpp>
#include <fcppt/log/warning.hpp>
#include <fcppt/text.hpp>

namespace
{

BYTE const
	key_up(
		0
	),
	key_down(
		0x80
	);

void
assign_state(
	BYTE &_key,
	bool const _value
)
{
	_key =
		_value
		?
			key_down
		:
			key_up;
}

}

sge::input::keyboard::char_type
sge::dinput::keycode_to_char(
	input::keyboard::key_code::type const _key,
	sge::input::keyboard::mod_state const &_modifiers,
	dinput::key_converter const &_conv,
	HKL const _kblayout
)
{
	typedef fcppt::container::array<
		BYTE,
		256
	> state_array;

	state_array state;

	assign_state(
		state[VK_SHIFT],
		modifiers & sge::input::keyboard::modifier::shift
	);

	assign_state(
		state[VK_MENU],
		modifiers & sge::input::keyboard::modifier::alt
	);

	assign_state(
		state[VK_CONTROL],
		modifiers & sge::input::keyboard::modifier::ctrl
	);

	UINT const
		dik(
			_conv.create_dik(
				_key
			),
		vk(
			::MapVirtualKeyEx(
				dik,
				1,
				_kblayout
			)
		);

	WORD result;

	switch(
		::ToAsciiEx(
			vk,
			dik,
			state.data(),
			&result,
			0,
			_kblayout
		)
	)
	{
	case 0:
		FCPPT_LOG_WARNING(
			sge::log::global(),
			fcppt::log::_
				<< FCPPT_TEXT("No translation found for dik: ")
				<< dik
		);

		return 0;
	case 1:
		return
			static_cast<
				fcppt::char_type
			>(
				result
			);
	case 2:
		FCPPT_LOG_WARNING(
			sge::log::global(),
			fcppt::log::_
				<< FCPPT_TEXT("stub: Key names with more than one char are not supported.")
			);

		return 0;
	default:
		throw sge::input::exception(
			FCPPT_TEXT("Invalid return value of ToAsciiEx!")
		);
	}
}
