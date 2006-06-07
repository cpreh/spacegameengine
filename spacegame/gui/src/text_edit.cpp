#include "../text_edit.hpp"
#include "../manager.hpp"
#include "../transform.hpp"
#include "../skin.hpp"

sge::gui::text_edit::text_edit(manager& m, element* const parent, const point pos, const dim sz, const std::string& _text, const color _text_color, const bool visible, const bool enabled)
: rectangle(m, parent, pos, sz, skin::textedit_name, visible, enabled),
  my_font(m.get_font()),
  _text(_text),
  _text_color(_text_color),
  text_start(0),
  cursor_pos(0),
  cur(m.get_sprite_system(),point(0,0),dim(height() / 10.f,height() * 0.9f), 500)
{}

void sge::gui::text_edit::on_key_press(const keyboard_button_event& event)
{
	const key_code key = event.code();
	const char char_code = event.char_code();

	switch(key) {
	case KC_LEFT:
		if(cursor_pos > 0)
			decrease_cursor_pos();
		break;
	case KC_RIGHT:
		if(cursor_pos < _text.size())
			increase_cursor_pos();
		break;
	case KC_HOME:
		cursor_pos = 0;
		break;
	case KC_END:
		cursor_pos = _text.size();
		break;
	case KC_BACK:
		if(cursor_pos > 0)
		{
			_text.erase(cursor_pos-1,1);
			decrease_cursor_pos();
		}
		break;
	case KC_DEL:
		if(cursor_pos < _text.size())
			_text.erase(cursor_pos,1);
		break;
	default:
		if(my_font.is_print(char_code))
		{
			_text.insert(cursor_pos,1,char_code);
			increase_cursor_pos();
		}
		break;
	}
}

void sge::gui::text_edit::on_click(const mouse_button_event& event)
{
	const unit x = event.pos().x;
	cursor_pos = text_start;
	std::string::size_type& i = cursor_pos;
	for(unit sz = 0; sz < x && i < _text.size(); ++i)
		sz += my_font.char_size(_text.at(i)).w;
}

void sge::gui::text_edit::increase_cursor_pos()
{
	++cursor_pos;
	while(my_font.string_size(_text,text_start,cursor_pos-text_start).w >= text_width())
		++text_start;
}

void sge::gui::text_edit::decrease_cursor_pos()
{
	--cursor_pos;
	if(cursor_pos <  text_start)
		text_start = cursor_pos;
}

void sge::gui::text_edit::on_draw(const draw_event& event)
{
	rectangle::on_draw(event);
	my_font.font_height(cur.height());
	my_font.draw_text(_text.substr(text_start,_text.size()-text_start), event.pos(), size(), _text_color, TXTF_AlignLeft | TXTF_AlignVCenter | TXTF_NoMultiLine);
	if(m.focus() == this)
	{
		point pos = event.pos();
		if(cursor_pos > 0 && cursor_pos <= _text.size())
			pos.x += my_font.string_size(_text, text_start, cursor_pos-text_start).w;

		pos.y += height() / 2 - cur.height() / 2;
		cur.pos(pos);
		cur.draw();
	}
}

void sge::gui::text_edit::text(const std::string& ntext)
{
	cursor_pos = text_start = 0;
	_text = ntext;
}

sge::gui::unit sge::gui::text_edit::text_height() const { return height()*0.8f; }
sge::gui::unit sge::gui::text_edit::text_width() const { return width()-0.01f; }

