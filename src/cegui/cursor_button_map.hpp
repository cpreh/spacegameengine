#ifndef SGE_CEGUI_CURSOR_BUTTON_MAP_HPP_INCLUDED
#define SGE_CEGUI_CURSOR_BUTTON_MAP_HPP_INCLUDED

#include <CEGUI/CEGUIInputEvent.h>
#include <sge/input/cursor/button_code.hpp>
#include <fcppt/container/map.hpp>
#include <map>

namespace sge
{
namespace cegui
{
typedef
fcppt::container::map
<
	std::map
	<
		sge::input::cursor::button_code::type,
		CEGUI::MouseButton
	>
>
cursor_button_map;
}
}

#endif
