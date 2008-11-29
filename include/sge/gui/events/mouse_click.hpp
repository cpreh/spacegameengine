#ifndef SGE_GUI_EVENTS_MOUSE_CLICK_HPP_INCLUDED
#define SGE_GUI_EVENTS_MOUSE_CLICK_HPP_INCLUDED

#include "../types.hpp"
#include "../../input/key_pair.hpp"
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
	SGE_SYMBOL mouse_click(point const &,input::key_pair const &);
	point const &pos() const { return pos_; }
	input::key_pair const &value() const { return kp; }
	private:
	point const pos_;
	input::key_pair const kp;
};
}
}
}

#endif
