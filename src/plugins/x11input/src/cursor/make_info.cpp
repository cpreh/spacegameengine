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


#include <sge/x11input/cursor/info.hpp>
#include <sge/x11input/cursor/make_info.hpp>
#include <sge/x11input/cursor/scroll_code.hpp>
#include <sge/x11input/cursor/scroll_valuator.hpp>
#include <sge/x11input/cursor/scroll_valuator_map.hpp>
#include <sge/x11input/device/valuator_index.hpp>
#include <sge/x11input/device/valuator_value.hpp>
#include <sge/x11input/device/info/class_cast.hpp>
#include <sge/x11input/device/info/class_type.hpp>
#include <fcppt/strong_typedef_construct_cast.hpp>
#include <fcppt/assert/unreachable.hpp>
#include <fcppt/config/external_begin.hpp>
#include <X11/extensions/XI2.h>
#include <X11/extensions/XInput2.h>
#include <utility>
#include <fcppt/config/external_end.hpp>


namespace
{

sge::x11input::device::valuator_value const
last_value(
	XIDeviceInfo const &,
	int number
);

}

sge::x11input::cursor::info const
sge::x11input::cursor::make_info(
	XIDeviceInfo const &_info
)
{
	sge::x11input::cursor::scroll_valuator_map scroll_valuators;

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
			sge::x11input::device::info::class_type(
				cur
			)
			==
			XIScrollClass
		)
		{
			XIScrollClassInfo const &scroll_class(
				sge::x11input::device::info::class_cast<
					XIScrollClassInfo const &
				>(
					cur
				)
			);

			scroll_valuators.insert(
				std::make_pair(
					fcppt::strong_typedef_construct_cast<
						sge::x11input::device::valuator_index
					>(
						scroll_class.number
					),
					sge::x11input::cursor::scroll_valuator(
						last_value(
							_info,
							scroll_class.number
						),
						sge::x11input::cursor::scroll_code(
							scroll_class.scroll_type
						)
					)
				)
			);
		}
	}

	return
		sge::x11input::cursor::info(
			scroll_valuators
		);
}

namespace
{

sge::x11input::device::valuator_value const
last_value(
	XIDeviceInfo const &_info,
	int const _number
)
{
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
			sge::x11input::device::info::class_type(
				cur
			)
			==
			XIValuatorClass
		)
		{
			XIValuatorClassInfo const &valuator_class(
				sge::x11input::device::info::class_cast<
					XIValuatorClassInfo const &
				>(
					cur
				)
			);

			if(
				valuator_class.number
				==
				_number
			)
				return
					sge::x11input::device::valuator_value(
						valuator_class.value
					);
		}
	}

	FCPPT_ASSERT_UNREACHABLE;
}

}
