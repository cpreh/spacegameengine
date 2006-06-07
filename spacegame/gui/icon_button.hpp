#ifndef SGE_GUI_ICON_BUTTON_HPP_INCLUDED
#define SGE_GUI_ICON_BUTTON_HPP_INCLUDED

#include "./types.hpp"
#include "./rectangle.hpp"

namespace sge
{
namespace gui
{
	class manager;

	class icon_button : public rectangle {
	public:
		SGEGUIDLLAPI icon_button(manager& m, element* parent, point pos, dim sz, const std::string& texture_released, const std::string& texture_hover,
		                         const std::string& texture_pressed, bool visible = true, bool enabled = true);
	private:
		SGEGUIDLLAPI virtual void on_draw(const draw_event& event);
		std::string texture_pressed,
		            texture_released,
		            texture_hover;
	};
	typedef shared_ptr<icon_button> icon_button_ptr;
}
}

#endif
