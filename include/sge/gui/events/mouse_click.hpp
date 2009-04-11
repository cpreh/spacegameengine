#ifndef SGE_GUI_EVENTS_MOUSE_CLICK_HPP_INCLUDED
#define SGE_GUI_EVENTS_MOUSE_CLICK_HPP_INCLUDED

#include <sge/gui/point.hpp>
#include <sge/gui/export.hpp>
#include <sge/input/key_pair.hpp>
#include <sge/math/vector/basic_impl.hpp>

namespace sge
{
namespace gui
{
namespace events
{
class mouse_click
{
	public:
	SGE_GUI_SYMBOL mouse_click(
		point const &,
		input::key_pair const &);
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
