#ifndef SGE_CEGUI_KEYBOARD_CODE_MAP_HPP_INCLUDED
#define SGE_CEGUI_KEYBOARD_CODE_MAP_HPP_INCLUDED

#include <CEGUI/CEGUIBase.h>
#include <sge/input/keyboard/key_code.hpp>
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
		sge::input::keyboard::key_code::type,
		CEGUI::uint
	>
>
keyboard_code_map;
}
}

#endif
