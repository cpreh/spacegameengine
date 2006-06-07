#include "../static_text.hpp"
#include "../manager.hpp"
#include "../skin.hpp"

sge::gui::static_text::static_text(manager& m, element* const parent, const std::string& text, const point pos, const dim sz, const color text_color, const bool visible, const bool enabled)
:  rectangle(m,parent,pos,sz,skin::statictext_name),
   text(text),
   text_color(text_color)
{}

void sge::gui::static_text::on_draw(const draw_event& event)
{
	rectangle::on_draw(event);
	m.get_font().draw_text(text,event.pos(),size(),text_color,TXTF_Default);
}
