#include "../static_text.hpp"
#include "../manager.hpp"
#include "../skin.hpp"

sge::gui::static_text::static_text(manager& m, element* const parent, const std::string& _text, const point pos, const dim sz, const color _text_color, const bool visible, const bool enabled)
:  rectangle(m,parent,pos,sz,skin::statictext_name),
   _text(_text),
   _text_color(_text_color)
{}

void sge::gui::static_text::on_draw(const draw_event& event)
{
	rectangle::on_draw(event);
	m.get_font().draw_text(_text, event.pos(), size(), _text_color, TXTF_Default);
}
