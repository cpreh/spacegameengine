/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2012 Carl Philipp Reh (sefi@s-e-f-i.de)

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
#include <sge/dinput/device/enumerate_objects.hpp>
#include <sge/dinput/joypad/enumerator.hpp>
#include <sge/dinput/joypad/info.hpp>
#include <sge/dinput/joypad/make_info.hpp>
#include <sge/input/info/name.hpp>
#include <sge/input/joypad/absolute_axis_info_container.hpp>
#include <sge/input/joypad/button_info_container.hpp>
#include <sge/input/joypad/info.hpp>
#include <sge/input/joypad/relative_axis_info_container.hpp>
#include <fcppt/string.hpp>


sge::dinput::joypad::info const
sge::dinput::joypad::make_info(
	IDirectInputDevice8 &_device,
	fcppt::string const &_name
)
{
	sge::dinput::joypad::enumerator object(
		_device
	);

	sge::dinput::device::enumerate_objects(
		_device,
		object,
		DIDFT_AXIS
		|
		DIDFT_BUTTON
	);

	return
		sge::dinput::joypad::info(
			sge::input::joypad::info(
				sge::input::joypad::absolute_axis_info_container(
					object.absolute_axis()
				),
				sge::input::joypad::button_info_container(
					object.buttons()
				),
				sge::input::joypad::relative_axis_info_container(
					object.relative_axis()
				),
				sge::input::info::name(
					_name
				)
			),
			object.absolute_axis_map(),
			object.button_map(),
			object.relative_axis_map()
		);
}
