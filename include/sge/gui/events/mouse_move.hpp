#ifndef SGE_GUI_EVENTS_MOUSE_MOVE_HPP_INCLUDED
#define SGE_GUI_EVENTS_MOUSE_MOVE_HPP_INCLUDED

#include "../types.hpp"
#include "../../export.hpp"

namespace sge
{
namespace gui
{
namespace events
{
class mouse_move
{
	public:
	SGE_SYMBOL mouse_move(point const &);
	point const &pos() const { return pos_; }
	private:
	point const pos_;
};
}
}
}

#endif
