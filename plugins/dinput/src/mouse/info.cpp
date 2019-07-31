//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/dinput/mouse/axis_map.hpp>
#include <sge/dinput/mouse/button_map.hpp>
#include <sge/dinput/mouse/info.hpp>
#include <sge/input/mouse/info.hpp>


sge::dinput::mouse::info::info(
	sge::input::mouse::info const &_input_info,
	sge::dinput::mouse::axis_map const &_axis_map,
	sge::dinput::mouse::button_map const &_button_map
)
:
	input_info_(
		_input_info
	),
	axis_map_(
		_axis_map
	),
	button_map_(
		_button_map
	)
{
}

sge::input::mouse::info const &
sge::dinput::mouse::info::input_info() const
{
	return
		input_info_;
}

sge::dinput::mouse::axis_map const &
sge::dinput::mouse::info::axis_map() const
{
	return
		axis_map_;
}

sge::dinput::mouse::button_map const &
sge::dinput::mouse::info::button_map() const
{
	return
		button_map_;
}
