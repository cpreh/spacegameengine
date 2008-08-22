#include <sge/gui/events/mouse_click.hpp>
#include <sge/assert.hpp>

sge::gui::events::mouse_click::mouse_click(
	point const &pos_,
	input::key_code const button_) 
	: pos_(pos_),
	  button_(button_)
{
	SGE_ASSERT(input::is_mouse_button(button()));
}
