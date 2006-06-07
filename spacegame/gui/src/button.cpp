#include "../button.hpp"
#include "../manager.hpp"
#include "../skin.hpp"

sge::gui::button::button(manager& m, element* const parent, const std::string& text,
                         const point pos, const dim sz, const color text_color, const bool visible, const bool enabled)
: rectangle(m,parent,pos,sz,skin::button_name,visible,enabled),
  text(text), text_color(text_color)
{}

void sge::gui::button::on_draw(const draw_event& event)
{
	if(pressed())
		set_texture(skin::button_pressed_name);
	else if(m.hover()==this)
		set_texture(skin::button_hover_name);
	else
		set_texture(skin::button_name);
	rectangle::on_draw(event);
	m.get_font().draw_text(text,event.pos(),size(),text_color,TXTF_AlignHCenter | TXTF_AlignVCenter);
}

