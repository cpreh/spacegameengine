#ifndef SGE_GUI_EVENTS_INVALID_AREA_HPP_INCLUDED
#define SGE_GUI_EVENTS_INVALID_AREA_HPP_INCLUDED

#include "../types.hpp"
#include "../canvas.hpp"

namespace sge
{
namespace gui
{
namespace events
{

class invalid_area
{
	public:
	// NOTE: this is a hack so we can create the 'canvas()' accessor function
	typedef sge::gui::canvas canvas_t;

	invalid_area(canvas_t);
	canvas_t &canvas() { return canvas_; }
	canvas_t const &canvas() const { return canvas_; }
	private:
	canvas_t canvas_;
};
}
}
}

#endif
