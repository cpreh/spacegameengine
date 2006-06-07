#include "../click_box.hpp"
#include "../manager.hpp"
#include "../skin.hpp"

sge::gui::click_box::click_box(manager& man, element* const parent, const point p, const style s, const bool v, const bool visible, const bool enabled)
: rectangle(man,parent,p,sz,"",visible,enabled),
  s(s), v(v)
{}

void sge::gui::click_box::on_click(const mouse_button_event&)
{
	v = !v;
}

void sge::gui::click_box::on_draw(const draw_event& event)
{
	switch(s) {
	case round:
		set_texture(v ? skin::clickbox_round_pressed_name : skin::clickbox_round_name);
		break;
	case quad:
		set_texture(v ? skin::clickbox_quad_pressed_name : skin::clickbox_quad_name);
		break;
	}
	rectangle::on_draw(event);
}

bool sge::gui::click_box::value() const { return v; }

const sge::dim sge::gui::click_box::sz(0.03f,0.03f);
