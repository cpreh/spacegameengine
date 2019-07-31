//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/input/info/name.hpp>
#include <sge/input/mouse/axis_info_container.hpp>
#include <sge/input/mouse/button_info_container.hpp>
#include <sge/input/mouse/info.hpp>
#include <fcppt/string.hpp>


sge::input::mouse::info::info(
	sge::input::mouse::axis_info_container const &_axes,
	sge::input::mouse::button_info_container const &_buttons,
	sge::input::info::name const &_name
)
:
	axes_(
		_axes
	),
	buttons_(
		_buttons
	),
	name_(
		_name
	)
{
}

sge::input::mouse::axis_info_container const &
sge::input::mouse::info::axes() const
{
	return axes_;
}

sge::input::mouse::button_info_container const &
sge::input::mouse::info::buttons() const
{
	return buttons_;
}

sge::input::info::name const &
sge::input::mouse::info::name() const
{
	return name_;
}
