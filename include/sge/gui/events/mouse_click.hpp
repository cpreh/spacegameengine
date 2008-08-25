#ifndef SGE_GUI_EVENTS_MOUSE_CLICK_HPP_INCLUDED
#define SGE_GUI_EVENTS_MOUSE_CLICK_HPP_INCLUDED

#include "../types.hpp"
#include "../../input/key_type.hpp"
#include "../../export.hpp"

namespace sge
{
namespace gui
{
namespace events
{
class mouse_click
{
	public:
	SGE_SYMBOL mouse_click(point const &,input::key_code const);
	point const &pos() const { return pos_; }
	input::key_code button() const { return button_; }
	private:
	point const pos_;
	input::key_code const button_;
};
}
}
}

#endif
