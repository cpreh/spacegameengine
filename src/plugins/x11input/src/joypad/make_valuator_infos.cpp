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


#include <sge/x11input/joypad/make_valuator_infos.hpp>
#include <sge/x11input/joypad/valuator_info.hpp>
#include <sge/x11input/joypad/valuator_info_vector.hpp>
#include <sge/x11input/device/info/class_type.hpp>
#include <sge/input/info/id.hpp>
#include <fcppt/assert/unreachable.hpp>
#include <fcppt/config/external_begin.hpp>
#include <X11/extensions/XI2.h>
#include <X11/extensions/XInput2.h>
#include <fcppt/config/external_end.hpp>

namespace
{

bool
is_absolute(
	int const _mode
)
{
	switch(
		_mode
	)
	{
	case XIModeAbsolute:
		return true;
	case XIModeRelative:
		return false;
	}

	FCPPT_ASSERT_UNREACHABLE
}

}

sge::x11input::joypad::valuator_info_vector const
sge::x11input::joypad::make_valuator_infos(
	XIDeviceInfo const &_info
)
{
	x11input::joypad::valuator_info_vector ret;

	input::info::id valuator_index(
		0u
	);

	for(
		int index = 0;
		index < _info.num_classes;
		++index
	)
	{
		XIAnyClassInfo const &cur(
			*_info.classes[
				index
			]
		);

		if(
			x11input::device::info::class_type(
				cur
			)
			!= XIValuatorClass
		)
			continue;

		ret.push_back(
			x11input::joypad::valuator_info(
				valuator_index,
				::is_absolute(
					reinterpret_cast<
						XIValuatorClassInfo const &
					>(
						cur
					).mode
				)
			)
		);

		++valuator_index;
	}

	return ret;
}
