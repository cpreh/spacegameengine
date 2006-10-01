#include "../check_box.hpp"
#include "../manager.hpp"
#include "../skin.hpp"

sge::gui::check_box::check_box(manager& man, element* const parent, const std::string& _text, const point pos, const dim sz, const color _text_color, const bool v, const bool visible, const bool enabled)
: rectangle(man, parent, pos, sz, skin::checkbox_name, visible, enabled),
  _text(_text), _text_color(_text_color),
  box(man,this, point(0,0.5*sz.h - 0.5*click_box::sz.h), click_box::quad, v)
{}

void sge::gui::check_box::on_draw(const draw_event& event)
{
	rectangle::on_draw(event);
	const dim cbsz(box.width(),0);
	m.get_font().draw_text(_text, event.pos() + point(cbsz.w,cbsz.h), size()-cbsz, _text_color, FTF_AlignLeft | FTF_AlignVCenter);
}

bool sge::gui::check_box::value() const
{
	return box.value();
}
