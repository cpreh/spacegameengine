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
		SGEGUIDLLAPI list(manager& m, element* parent, point pos, dim sz, unit line_height = 0.05, color text_color = colors::black, bool visible = true, bool enabled = true);
		SGEGUIDLLAPI void push_back(const std::string& str);
		SGEGUIDLLAPI void pop_back();
		SGEGUIDLLAPI void clear();
		SGEGUIDLLAPI void delete_element(size_type index);
		SGEGUIDLLAPI difference_type selected_index() const;
		SGEGUIDLLAPI const std::string& selected() const;
		SGEGUIDLLAPI std::string& selected();
		SGEGUIDLLAPI const std::string& operator[](size_type index) const;
		SGEGUIDLLAPI std::string& operator[](size_type index);
		SGEGUIDLLAPI size_type size() const;
	private:
		SGEGUIDLLAPI virtual void on_draw(const draw_event& event);
		SGEGUIDLLAPI virtual void on_click(const mouse_button_event& event);
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
