#include "mouse_click.hpp"
#include <cassert>

sge::gui::events::mouse_click::mouse_click(
	point const &pos_,
	input::key_code const button_) 
	: pos_(pos_),
	  button_(button_)
{
	assert(input::is_mouse_button(button()));
}
