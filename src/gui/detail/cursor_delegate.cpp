/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2009 Carl Philipp Reh (sefi@s-e-f-i.de)

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
#include <sge/input/key_pair.hpp>
#include <fcppt/text.hpp>
#include <algorithm>

sge::gui::detail::cursor_delegate::cursor_delegate(string &text)
	: text(text),
	  pos_(text.length())
{
}

fcppt::string::size_type
sge::gui::detail::cursor_delegate::pos() const
{
	return pos_;
}

void sge::gui::detail::cursor_delegate::key_callback(
	input::key_pair const &c)
{
	switch (c.key().code())
	{
		case input::kc::key_return:
			text += FCPPT_TEXT('\n');
		break;
		case input::kc::key_left:
			if (pos_ == 0)
				return;

			pos_--;

			if (text[pos_] == FCPPT_TEXT('\n'))
				pos_--;
		break;
		case input::kc::key_right:
			pos_ = std::min(pos_+1,text.length());
			if (text[pos_] == FCPPT_TEXT('\n'))
				pos_++;
		break;
		case input::kc::key_backspace:
			if (pos_ == 0)
				return;

			text.erase(text.begin()+(pos_-1));
			pos_--;
		break;
		default:
			if (c.key().char_code() == 0)
				return;

			text.insert(
				text.begin()+pos_,
				c.key().char_code());

			pos_++;
		break;
	}
}
