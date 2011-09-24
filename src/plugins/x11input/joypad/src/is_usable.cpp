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


#include "../is_usable.hpp"
#include "../../device/id.hpp"
#include "../../device/info.hpp"
#include <sge/input/exception.hpp>
#include <awl/backends/x11/display_fwd.hpp>
#include <fcppt/config/external_begin.hpp>
#include <X11/extensions/XInput2.h>
#include <X11/extensions/XI2.h>
#include <fcppt/config/external_end.hpp>

bool
sge::x11input::joypad::is_usable(
	awl::backends::x11::display &_display,
	x11input::device::id const _id
)
try
{
	// maybe it can happen that this device is already gone
	x11input::device::info const info(
		_display,
		_id
	);

	bool
		has_valuators(
			false
		),
		has_buttons(
			false
		);

	XIAnyClassInfo **classes(
		info.get().classes
	);


	for(
		int index(0);
		index < info.get().num_classes;
		++index
	)
		switch(
			classes[
				index
			]->type
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
catch(
	sge::input::exception const &
)
{
	return false;
}
