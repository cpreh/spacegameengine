#ifndef SGE_GUI_EVENTS_MOUSE_MOVE_HPP_INCLUDED
#define SGE_GUI_EVENTS_MOUSE_MOVE_HPP_INCLUDED

#include <sge/gui/point.hpp>
#include <sge/gui/export.hpp>

namespace sge
{
namespace gui
{
namespace events
{
class mouse_move
{
	public:
	SGE_GUI_SYMBOL mouse_move(point const &);
	point const &pos() const { return pos_; }
	private:
	point const pos_;
};
}
}
}

#endif
