#ifndef SGE_GUI_SCROLLBAR_HPP_INCLUDED
#define SGE_GUI_SCROLLBAR_HPP_INCLUDED

#include "./rectangle.hpp"
#include <boost/function.hpp>

namespace sge
{
namespace gui
{

class manager;

class inner_scrollbar : public rectangle {
public:
	inner_scrollbar(manager& m, element* parent, point pos, dim sz);
private:
	virtual void on_draw(const draw_event& event);
};

class scroll_button : public rectangle {
public:
	enum style { up_scroll, down_scroll };
	typedef boost::function<void()> action_function;
	scroll_button(manager& m, element* parent, point pos, dim sz, style s, action_function action);
private:
	virtual void on_mouse_press(const mouse_button_event& event);
	virtual void on_click(const mouse_button_event& event);
	virtual void on_draw(const draw_event& event);
	action_function action;
};

}
}

#endif
