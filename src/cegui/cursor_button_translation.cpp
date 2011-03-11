#include "cursor_button_translation.hpp"
#include <sge/input/cursor/button_code.hpp>
#include <CEGUI/CEGUIInputEvent.h>

sge::cegui::cursor_button_map const &
sge::cegui::cursor_button_translation()
{
	static cursor_button_map buttons;
	if (!buttons.empty())
		return buttons;
	buttons.insert(
		sge::input::cursor::button_code::left,
		CEGUI::LeftButton);
	buttons.insert(
		sge::input::cursor::button_code::right,
		CEGUI::RightButton);
	buttons.insert(
		sge::input::cursor::button_code::middle,
		CEGUI::MiddleButton);
	return buttons;
}
