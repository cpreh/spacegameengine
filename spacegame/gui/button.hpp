#ifndef SGE_GUI_BUTTON_HPP_INCLUDED
#define SGE_GUI_BUTTON_HPP_INCLUDED

#include "./rectangle.hpp"
#include "./types.hpp"

namespace sge
{
namespace gui {
	class manager;

	class button : public rectangle {
	public:
		SGEGUIDLLAPI button(manager& m, element* parent, const std::string& text, point pos, dim sz, color text_color = colors::white, bool visible = true, bool enabled = true);
		void text(const std::string&);
		const std::string& text() const { return _text; }
		void text_color(color c) { _col = c; }
		color text_color() const { return _col; }
	private:
		std::string _text;
		color       _col;
		SGEGUIDLLAPI virtual void on_draw(const draw_event& event);
	};
	typedef shared_ptr<button> button_ptr;
}
}

#endif
