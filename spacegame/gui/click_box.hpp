#ifndef SGE_GUI_CLICK_BOX_HPP_INCLUDED
#define SGE_GUI_CLICK_BOX_HPP_INCLUDED

#include "./types.hpp"
#include "./rectangle.hpp"

namespace sge
{
namespace gui
{
	class manager;
	
	class click_box : public rectangle {
	public:
		enum style { round, quad };
		SGEGUIDLLAPI click_box(manager& man, element* parent, point pos, style s = quad, bool value = false, bool visible = true, bool enabled = true);
		SGEGUIDLLAPI bool value() const;
		static const dim sz;
	private:
		SGEGUIDLLAPI virtual void on_click(const mouse_button_event& event);
		SGEGUIDLLAPI virtual void on_draw(const draw_event& event);
		style s;
		bool  v;
	};
	typedef shared_ptr<click_box> click_box_ptr;
}
}

#endif
