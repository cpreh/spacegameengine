/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2011 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#include <sge/x11input/joypad/axis_infos.hpp>
#include <sge/x11input/joypad/axis_code.hpp>
#include <sge/x11input/device/info/string_from_atom.hpp>
#include <sge/input/joypad/axis_info.hpp>
#include <sge/input/joypad/axis_info_container.hpp>
#include <fcppt/config/external_begin.hpp>
#include <X11/extensions/XInput2.h>
#include <fcppt/config/external_end.hpp>

sge::input::joypad::axis_info_container const
sge::x11input::joypad::axis_infos(
	awl::backends::x11::display &_display,
	XIDeviceInfo const &_info
)
{
	sge::input::joypad::axis_info_container::vector ret;

	XIAnyClassInfo **classes(
		_info.classes
	);

	for(
		int index(0);
		index < _info.num_classes;
		++index
	)
	{
		XIAnyClassInfo const &any(
			*classes[index]
		);

		if(
			any.type
			!= XIValuatorClass
		)
			continue;

		XIValuatorClassInfo const &valuator_info(
			reinterpret_cast<
				XIValuatorClassInfo const &
			>(
				any
			)
		);

		ret.push_back(
			sge::input::joypad::axis_info(
				joypad::axis_code(
					valuator_info
				),
				x11input::device::info::string_from_atom(
					_display,
					valuator_info.label
				)
			)
		);
	}

	return
		sge::input::joypad::axis_info_container(
			ret
		);
}
