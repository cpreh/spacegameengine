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


#include <sge/x11input/device/info/class_type.hpp>
#include <sge/x11input/joypad/is_usable.hpp>
#include <fcppt/config/external_begin.hpp>
#include <X11/extensions/XI2.h>
#include <X11/extensions/XInput2.h>
#include <fcppt/config/external_end.hpp>


bool
sge::x11input::joypad::is_usable(
	XIDeviceInfo const &_info
)
{
	// TODO: can we query if a device is joypad directly?
	bool
		has_valuators(
			false
		),
		has_buttons(
			false
		);

	XIAnyClassInfo **classes(
		_info.classes
	);


	for(
		int index(0);
		index < _info.num_classes;
		++index
	)
		switch(
			x11input::device::info::class_type(
				*classes[
					index
				]
			)
		)
		{
		case XIButtonClass:
			has_buttons = true;
			break;
		case XIValuatorClass:
			has_valuators = true;
			break;
		}

	return
		has_valuators
		&& has_buttons;
}
