#ifndef SGE_GUI_LIST_HPP_INCLUDED
#define SGE_GUI_LIST_HPP_INCLUDED

#include <cstddef>
#include <deque>
#include "./rectangle.hpp"
#include "./vertical_scrollbar.hpp"
#include "./line_strip.hpp"

namespace sge
{

class font;

namespace gui
{

class list : public rectangle {
public:
	typedef std::size_t     size_type;
	typedef std::ptrdiff_t  difference_type;
	static const difference_type no_selection = -1;
	list(manager& m, element* parent, point pos, dim sz, unit line_height = 0.05, color text_color = colors::black, bool visible = true, bool enabled = true);
	void push_back(const std::string& str);
	void pop_back();
	void clear();
	void delete_element(size_type index);
	difference_type selected_index() const;
	const std::string& selected() const;
	std::string& selected();
	const std::string& operator[](size_type index) const;
	std::string& operator[](size_type index);
	size_type size() const;
private:
	virtual void on_draw(const draw_event& event);
	virtual void on_click(const mouse_button_event& event);
	void scroll_position_change(size_type npos);
	void calc_scrollbar();

	typedef std::deque<std::string> element_queue;
	font&                  my_font;
	color                  text_color;
	unit                   line_height;
	element_queue          elements;
	vertical_scrollbar     vscrollbar;
	difference_type        selected_;
};

typedef shared_ptr<list> list_ptr;

}
}

#endif
