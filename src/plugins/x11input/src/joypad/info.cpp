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


#include <sge/input/joypad/absolute_axis_info_container.hpp>
#include <sge/input/joypad/button_info_container.hpp>
#include <sge/input/joypad/info.hpp>
#include <sge/input/joypad/relative_axis_info_container.hpp>
#include <sge/x11input/device/info/class_type.hpp>
#include <sge/x11input/device/info/name.hpp>
#include <sge/x11input/joypad/absolute_axis_info.hpp>
#include <sge/x11input/joypad/button_infos.hpp>
#include <sge/x11input/joypad/info.hpp>
#include <sge/x11input/joypad/relative_axis_info.hpp>
#include <awl/backends/x11/display_fwd.hpp>
#include <fcppt/assert/error.hpp>
#include <fcppt/config/external_begin.hpp>
#include <X11/extensions/XI2.h>
#include <X11/extensions/XInput2.h>
#include <fcppt/config/external_end.hpp>


sge::input::joypad::info const
sge::x11input::joypad::info(
	awl::backends::x11::display &_display,
	XIDeviceInfo const &_info
)
{
	sge::input::joypad::absolute_axis_info_container::vector absolute_axis;

	sge::input::joypad::button_info_container::vector buttons;

	sge::input::joypad::relative_axis_info_container::vector relative_axis;

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

		switch(
			x11input::device::info::class_type(
				cur
			)
		)
		{
		case XIButtonClass:
			FCPPT_ASSERT_ERROR(
				buttons.empty()
			);

			buttons =
				sge::x11input::joypad::button_infos(
					reinterpret_cast<
						XIButtonClassInfo const &
					>(
						cur
					),
					_display
				);
			break;
		case XIValuatorClass:
			{
				XIValuatorClassInfo const &valuator_class(
					reinterpret_cast<
						XIValuatorClassInfo const &
					>(
						cur
					)
				);

				switch(
					valuator_class.mode
				)
				{
				case XIModeAbsolute:
					absolute_axis.push_back(
						sge::x11input::joypad::absolute_axis_info(
							valuator_class,
							_display
						)
					);
					break;
				case XIModeRelative:
					relative_axis.push_back(
						sge::x11input::joypad::relative_axis_info(
							valuator_class,
							_display
						)
					);
					break;
				}
			}
			break;
		}
	}

	return
		sge::input::joypad::info(
			sge::input::joypad::absolute_axis_info_container(
				absolute_axis
			),
			sge::input::joypad::button_info_container(
				buttons
			),
			sge::input::joypad::relative_axis_info_container(
				relative_axis
			),
			x11input::device::info::name(
				_info
			)
		);
}
