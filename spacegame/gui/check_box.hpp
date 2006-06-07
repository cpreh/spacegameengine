#ifndef SGE_GUI_CHECK_BOX_HPP_INCLUDED
#define SGE_GUI_CHECK_BOX_HPP_INCLUDED

#include "./types.hpp"
#include "./rectangle.hpp"
#include "./click_box.hpp"

namespace sge
{
namespace gui
{
	class manager;

	class check_box : public rectangle {
	public:
		SGEGUIDLLAPI check_box(manager& man, element* parent, const std::string& text, point pos, dim size, color text_color = colors::white, bool value = false, bool visible = true, bool enabled = true);
		SGEGUIDLLAPI bool value() const;
		void text(const std::string& t) { _text = t; }
		const std::string& text() const { return _text; }
		void text_color(const color c) { _text_color = c; }
		color text_color() const { return _text_color; }
	private:
		SGEGUIDLLAPI virtual void on_draw(const draw_event& event);
		std::string _text;
		color       _text_color;
		click_box box;
	};
	typedef shared_ptr<check_box> check_box_ptr;
}
}

#endif
