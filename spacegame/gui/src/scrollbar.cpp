#include "../scrollbar.hpp"
#include "../manager.hpp"
#include "../skin.hpp"

sge::gui::inner_scrollbar::inner_scrollbar(manager& m, element* const parent, const point pos, const dim sz)
: rectangle(m,parent,pos,sz,skin::inner_scrollbar_name)
{}

void sge::gui::inner_scrollbar::on_draw(const draw_event& event)
{
	rectangle::on_draw(event);
}


sge::gui::scroll_button::scroll_button(manager& m, element* const parent, const point pos, const dim sz, const style _style, const action_function action)
: rectangle(m,parent,pos,sz,_style == up_scroll ? skin::up_scrollbutton_name : skin::down_scrollbutton_name), action(action)
{}

void sge::gui::scroll_button::on_mouse_press(const mouse_button_event&)
{
	action();
}

void sge::gui::scroll_button::on_click(const mouse_button_event&)
{
	action();
}

void sge::gui::scroll_button::on_draw(const draw_event& event)
{
	rectangle::on_draw(event);
}
