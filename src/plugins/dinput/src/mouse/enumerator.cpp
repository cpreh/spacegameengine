/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2014 Carl Philipp Reh (carlphilippreh <at> gmail.com)

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU Lesser General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
*/


#include <sge/dinput/di.hpp>
#include <sge/dinput/device/add_element.hpp>
#include <sge/dinput/device/enumerator.hpp>
#include <sge/dinput/mouse/axis_map.hpp>
#include <sge/dinput/mouse/button_map.hpp>
#include <sge/dinput/mouse/enumerator.hpp>
#include <sge/dinput/mouse/is_axis.hpp>
#include <sge/dinput/mouse/make_axis_info.hpp>
#include <sge/dinput/mouse/make_button_info.hpp>
#include <sge/input/mouse/axis_info.hpp>
#include <sge/input/mouse/axis_info_container.hpp>
#include <sge/input/mouse/button_info.hpp>
#include <sge/input/mouse/button_info_container.hpp>


sge::dinput::mouse::enumerator::enumerator()
:
	sge::dinput::device::enumerator(),
	axis_(),
	buttons_(),
	axis_map_(),
	button_map_()
{
}

sge::dinput::mouse::enumerator::~enumerator()
{
}

sge::input::mouse::axis_info_container::vector const &
sge::dinput::mouse::enumerator::axis() const
{
	return
		axis_;
}

sge::input::mouse::button_info_container::vector const &
sge::dinput::mouse::enumerator::buttons() const
{
	return
		buttons_;
}

sge::dinput::mouse::axis_map const &
sge::dinput::mouse::enumerator::axis_map() const
{
	return
		axis_map_;
}

sge::dinput::mouse::button_map const &
sge::dinput::mouse::enumerator::button_map() const
{
	return
		button_map_;
}

void
sge::dinput::mouse::enumerator::dispatch(
	DIDEVICEOBJECTINSTANCE const &_data
)
{
	if(
		sge::dinput::mouse::is_axis(
			_data.guidType
		)
	)
		sge::dinput::device::add_element(
			_data,
			axis_map_,
			axis_,
			&sge::dinput::mouse::make_axis_info
		);
	else if(
		_data.guidType == GUID_Button
	)
		sge::dinput::device::add_element(
			_data,
			button_map_,
			buttons_,
			&sge::dinput::mouse::make_button_info
		);
}
