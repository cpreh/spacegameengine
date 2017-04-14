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


#include <sge/charconv/utf8_string.hpp>
#include <sge/wlinput/focus/get_utf8_string.hpp>
#include <sge/wlinput/focus/state.hpp>
#include <sge/wlinput/focus/xkb_keycode.hpp>
#include <fcppt/assert/error.hpp>
#include <fcppt/cast/to_unsigned.hpp>
#include <fcppt/container/dynamic_array_impl.hpp>


sge::charconv::utf8_string
sge::wlinput::focus::get_utf8_string(
	sge::wlinput::focus::state const &_state,
	sge::wlinput::focus::xkb_keycode const _keycode
)
{
	int const size{
		::xkb_state_key_get_utf8(
			_state.get(),
			_keycode.get(),
			nullptr,
			0
		)
	};

	FCPPT_ASSERT_ERROR(
		size
		>=
		0
	);

	fcppt::container::dynamic_array<
		char
	> buffer(
		fcppt::cast::to_unsigned(
			size
		)
		+
		1u
	);

	FCPPT_ASSERT_ERROR(
		::xkb_state_key_get_utf8(
			_state.get(),
			_keycode.get(),
			buffer.data(),
			buffer.size()
		)
		==
		size
	);

	return
		sge::charconv::utf8_string{
			buffer.data()
		};
}
