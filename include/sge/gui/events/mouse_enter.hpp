#ifndef SGE_GUI_EVENTS_MOUSE_ENTER_HPP_INCLUDED
#define SGE_GUI_EVENTS_MOUSE_ENTER_HPP_INCLUDED

#include "../types.hpp"

namespace sge
{
namespace gui
{
namespace events
{
class mouse_enter
{
	public:
	mouse_enter(point const &);
	point const &pos() const { return pos_; }
	private:
	point const pos_;
};
}
}
}

#endif
