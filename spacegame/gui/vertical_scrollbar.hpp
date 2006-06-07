#ifndef SGE_GUI_VERTICAL_SCROLLBAR_HPP_INCLUDED
#define SGE_GUI_VERTICAL_SCROLLBAR_HPP_INCLUDED

#include <cstddef>
#include "./rectangle.hpp"
#include "./scrollbar.hpp"

namespace sge
{
namespace gui
{
	class manager;

	class vertical_scrollbar : public rectangle {
	public:
		typedef std::size_t size_type;
		SGEGUIDLLAPI vertical_scrollbar(manager& m, element* parent, point pos, dim sz, bool visible = true, bool enabled = true);
		SGEGUIDLLAPI void scroll_max(size_type max);
		size_type scroll_pos() const { return s_pos; }
	protected:
		void up_scroll_action();
		void down_scroll_action();
		virtual void scroll_position_change(size_type newpos){}
	private:
		SGEGUIDLLAPI void on_glob_mouse_move(const mouse_move_event& event);
		SGEGUIDLLAPI void on_mouse_up(const mouse_button_event& event);
		SGEGUIDLLAPI void on_mouse_press(const mouse_button_event& event);
		SGEGUIDLLAPI void on_mouse_down(const mouse_button_event& event);
		void move_scrollbar(point click_pos);
		void recalc_pos();
		unit scroll_max_h() const;
		size_type s_pos,
		          s_max;
		inner_scrollbar scrollbar;
		scroll_button up_scroll_button,
			      down_scroll_button;
	};
	typedef shared_ptr<vertical_scrollbar> vertical_scrollbar_ptr;
}
}

#endif
