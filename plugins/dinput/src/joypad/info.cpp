//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/dinput/joypad/absolute_axis_map.hpp>
#include <sge/dinput/joypad/button_map.hpp>
#include <sge/dinput/joypad/info.hpp>
#include <sge/dinput/joypad/relative_axis_map.hpp>
#include <sge/input/joypad/info.hpp>


sge::dinput::joypad::info::info(
	sge::input::joypad::info const &_input_info,
	sge::dinput::joypad::absolute_axis_map const &_absolute_axis_map,
	sge::dinput::joypad::button_map const &_button_map,
	sge::dinput::joypad::relative_axis_map const &_relative_axis_map
)
:
	input_info_(
		_input_info
	),
	absolute_axis_map_(
		_absolute_axis_map
	),
	button_map_(
		_button_map
	),
	relative_axis_map_(
		_relative_axis_map
	)
{
}

sge::input::joypad::info const &
sge::dinput::joypad::info::input_info() const
{
	return
		input_info_;
}

sge::dinput::joypad::absolute_axis_map const &
sge::dinput::joypad::info::absolute_axis_map() const
{
	return
		absolute_axis_map_;
}

sge::dinput::joypad::button_map const &
sge::dinput::joypad::info::button_map() const
{
	return
		button_map_;
}

sge::dinput::joypad::relative_axis_map const &
sge::dinput::joypad::info::relative_axis_map() const
{
	return
		relative_axis_map_;
}
