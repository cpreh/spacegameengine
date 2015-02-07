/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2015 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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


#include <sge/input/mouse/axis_info_container.hpp>
#include <sge/input/mouse/button_info_container.hpp>
#include <sge/input/mouse/info.hpp>
#include <sge/x11input/device/info/class_cast.hpp>
#include <sge/x11input/device/info/class_type.hpp>
#include <sge/x11input/device/info/name.hpp>
#include <sge/x11input/mouse/axis_info.hpp>
#include <sge/x11input/mouse/button_infos.hpp>
#include <sge/x11input/mouse/info.hpp>
#include <awl/backends/x11/display_fwd.hpp>
#include <fcppt/make_int_range_count.hpp>
#include <fcppt/assert/error.hpp>
#include <fcppt/config/external_begin.hpp>
#include <X11/extensions/XInput2.h>
#include <fcppt/config/external_end.hpp>


sge::input::mouse::info
sge::x11input::mouse::info(
	awl::backends::x11::display &_display,
	XIDeviceInfo const &_info
)
{
	sge::input::mouse::axis_info_container::vector axis;

	sge::input::mouse::button_info_container::vector buttons;

	for(
		int const index
		:
		fcppt::make_int_range_count(
			_info.num_classes
		)
	)
	{
		XIAnyClassInfo const &cur(
			*_info.classes[
				index
			]
		);

		switch(
			sge::x11input::device::info::class_type(
				cur
			)
		)
		{
		case XIButtonClass:
			FCPPT_ASSERT_ERROR(
				buttons.empty()
			);

			buttons =
				sge::x11input::mouse::button_infos(
					sge::x11input::device::info::class_cast<
						XIButtonClassInfo const &
					>(
						cur
					),
					_display
				);
			break;
		case XIValuatorClass:
			axis.push_back(
				sge::x11input::mouse::axis_info(
					sge::x11input::device::info::class_cast<
						XIValuatorClassInfo const &
					>(
						cur
					),
					_display
				)
			);
			break;
		}
	}

	return
		sge::input::mouse::info(
			sge::input::mouse::axis_info_container(
				axis
			),
			sge::input::mouse::button_info_container(
				buttons
			),
			sge::x11input::device::info::name(
				_info
			)
		);
}
