#ifndef SGE_GUI_STATIC_TEXT_HPP_INCLUDED
#define SGE_GUI_STATIC_TEXT_HPP_INCLUDED

#include "../shared_ptr.hpp"
#include "./types.hpp"
#include "./rectangle.hpp"

namespace sge
{
namespace gui
{

class manager;

class static_text : public rectangle {
public:
	static_text(manager& m, element* parent, const std::string& text, point pos, dim sz, color text_color = colors::black, bool visible = true, bool enabled = true);
	const std::string& text() const { return _text; }
	void text(const std::string& t) { _text = t; }
	color text_color() const { return _text_color; }
	void text_color(const color c) { _text_color = c; }
private:
	std::string _text;
	color _text_color;
	virtual void on_draw(const draw_event& event);
};

typedef shared_ptr<static_text> static_text_ptr;

}
}

#endif
