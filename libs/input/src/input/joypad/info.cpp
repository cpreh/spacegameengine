//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/input/info/name.hpp>
#include <sge/input/info/unique_id.hpp>
#include <sge/input/joypad/absolute_axis_info_container.hpp>
#include <sge/input/joypad/button_info_container.hpp>
#include <sge/input/joypad/info.hpp>
#include <sge/input/joypad/relative_axis_info_container.hpp>
#include <sge/input/joypad/ff/type_field.hpp>


sge::input::joypad::info::info(
	sge::input::joypad::absolute_axis_info_container const &_absolute_axes,
	sge::input::joypad::button_info_container const &_buttons,
	sge::input::joypad::relative_axis_info_container const &_relative_axes,
	sge::input::joypad::ff::type_field const _ff_types,
	sge::input::info::name const &_name,
	sge::input::info::unique_id const &_unique_id
)
:
	absolute_axes_(
		_absolute_axes
	),
	buttons_(
		_buttons
	),
	relative_axes_(
		_relative_axes
	),
	ff_types_(
		_ff_types
	),
	name_(
		_name
	),
	unique_id_(
		_unique_id
	)
{
}

sge::input::joypad::absolute_axis_info_container const &
sge::input::joypad::info::absolute_axes() const
{
	return
		absolute_axes_;
}

sge::input::joypad::button_info_container const &
sge::input::joypad::info::buttons() const
{
	return
		buttons_;
}

sge::input::joypad::relative_axis_info_container const &
sge::input::joypad::info::relative_axes() const
{
	return
		relative_axes_;
}

sge::input::joypad::ff::type_field
sge::input::joypad::info::ff_types() const
{
	return
		ff_types_;
}

sge::input::info::name const &
sge::input::joypad::info::name() const
{
	return
		name_;
}

sge::input::info::unique_id const &
sge::input::joypad::info::unique_id() const
{
	return
		unique_id_;
}
