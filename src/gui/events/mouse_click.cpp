#include <sge/gui/events/mouse_click.hpp>
#include <sge/input/classification.hpp>
#include <sge/assert.hpp>

sge::gui::events::mouse_click::mouse_click(
	point const &pos_,
	input::key_pair const &kp) 
	: pos_(pos_),
	  kp(kp)
{
	SGE_ASSERT(input::is_mouse_button(kp.key().code()));
}
