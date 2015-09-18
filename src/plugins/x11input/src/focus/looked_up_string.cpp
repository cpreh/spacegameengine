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


#include <sge/input/key/code.hpp>
#include <sge/x11input/focus/char_vector.hpp>
#include <sge/x11input/focus/looked_up_string.hpp>
#include <fcppt/config/external_begin.hpp>
#include <utility>
#include <fcppt/config/external_end.hpp>


sge::x11input::focus::looked_up_string::looked_up_string(
	sge::x11input::focus::char_vector &&_char_codes,
	sge::input::key::code const _key_code
)
:
	char_codes_(
		std::move(
			_char_codes
		)
	),
	key_code_(
		_key_code
	)
{
}

sge::x11input::focus::char_vector const &
sge::x11input::focus::looked_up_string::char_codes() const
{
	return
		char_codes_;
}

sge::input::key::code
sge::x11input::focus::looked_up_string::key_code() const
{
	return
		key_code_;
}
