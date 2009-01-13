#include <sge/gui/detail/cursor_delegate.hpp>
#include <sge/input/key_pair.hpp>
#include <sge/text.hpp>
#include <algorithm>

sge::gui::detail::cursor_delegate::cursor_delegate(string &text)
	: text(text),
	  pos_(text.length())
{
}

void sge::gui::detail::cursor_delegate::key_callback(
	input::key_pair const &c)
{
	switch (c.key().code())
	{
		case input::kc::key_return:
			text += SGE_TEXT('\n');
		break;
		case input::kc::key_left:
			if (pos_ == 0)
				return;
			
			pos_--;

			if (text[pos_] == SGE_TEXT('\n'))
				pos_--;
		break;
		case input::kc::key_right:
			pos_ = std::min(pos_+1,text.length());
			if (text[pos_] == SGE_TEXT('\n'))
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
