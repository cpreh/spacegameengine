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


#include <sge/gui/detail/cursor_delegate.hpp>
#include <sge/input/keyboard/key_event.hpp>
#include <fcppt/text.hpp>
#include <algorithm>

sge::gui::detail::cursor_delegate::cursor_delegate(fcppt::string &text)
:
	text(text),
	pos_(text.length())
{
}

fcppt::string::size_type
sge::gui::detail::cursor_delegate::pos() const
{
	return pos_;
}

void
sge::gui::detail::cursor_delegate::key_callback(
	input::keyboard::key_event const &c
)
{
	switch (c.key().code())
	{
		case input::keyboard::key_code::return_:
			text += FCPPT_TEXT('\n');
		break;
		case input::keyboard::key_code::left:
			if (pos_ == 0)
				return;

			pos_--;

			if (text[pos_] == FCPPT_TEXT('\n'))
				pos_--;
		break;
		case input::keyboard::key_code::right:
			pos_ = std::min(pos_+1,text.length());
			if (text[pos_] == FCPPT_TEXT('\n'))
				pos_++;
		break;
		case input::keyboard::key_code::backspace:
			if (pos_ == 0)
				return;

			text.erase(
				text.begin()
				+
				static_cast<
					fcppt::string::iterator::difference_type
				>(
					pos_
				)
				-1
			);

			pos_--;
		break;
		default:
			if (c.key().character() == 0)
				return;

			text.insert(
				text.begin()
				+
				static_cast<
					fcppt::string::iterator::difference_type
				>(
					pos_
				),
				c.key().character());

			pos_++;
		break;
	}
}
