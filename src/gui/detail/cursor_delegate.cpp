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


#include <sge/gui/detail/cursor_delegate.hpp>
#include <sge/input/keyboard/key_event.hpp>
#include <sge/font/text/lit.hpp>
#include <algorithm>

sge::gui::detail::cursor_delegate::cursor_delegate(
	sge::font::text::string &_text
)
:
	text_(_text),
	pos_(_text.length())
{
}

sge::font::text::string::size_type
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
			text_ += SGE_FONT_TEXT_LIT('\n');
		break;
		case input::keyboard::key_code::left:
			if (pos_ == 0)
				return;

			pos_--;

			if (text_[pos_] == SGE_FONT_TEXT_LIT('\n'))
				pos_--;
		break;
		case input::keyboard::key_code::right:
			pos_ = std::min(pos_+1,text_.length());
			if (text_[pos_] == SGE_FONT_TEXT_LIT('\n'))
				pos_++;
		break;
		case input::keyboard::key_code::backspace:
			if (pos_ == 0)
				return;

			text_.erase(
				text_.begin()
				+
				static_cast<
					sge::font::text::string::iterator::difference_type
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

			text_.insert(
				text_.begin()
				+
				static_cast<
					sge::font::text::string::iterator::difference_type
				>(
					pos_
				),
				c.key().character());

			pos_++;
		break;
	}
}
