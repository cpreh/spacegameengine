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


#include <sge/x11input/cursor/find_scroll_valuator.hpp>
#include <sge/x11input/cursor/make_scroll_valuators.hpp>
#include <sge/x11input/cursor/scroll_code.hpp>
#include <sge/x11input/cursor/scroll_valuator.hpp>
#include <sge/x11input/cursor/scroll_valuator_map.hpp>
#include <sge/x11input/device/valuator/index.hpp>
#include <sge/x11input/device/valuator/make_absolute.hpp>
#include <sge/x11input/device/info/class_cast.hpp>
#include <sge/x11input/device/info/class_type.hpp>
#include <fcppt/make_int_range_count.hpp>
#include <fcppt/optional_impl.hpp>
#include <fcppt/algorithm/map_optional.hpp>
#include <fcppt/config/external_begin.hpp>
#include <X11/extensions/XI2.h>
#include <X11/extensions/XInput2.h>
#include <utility>
#include <fcppt/config/external_end.hpp>


sge::x11input::cursor::scroll_valuator_map
sge::x11input::cursor::make_scroll_valuators(
	XIDeviceInfo const &_info
)
{
	return
		fcppt::algorithm::map_optional<
			sge::x11input::cursor::scroll_valuator_map
		>(
			fcppt::make_int_range_count(
				_info.num_classes
			),
			[
				&_info
			](
				int const _index
			)
			{
				XIAnyClassInfo const &cur(
					*_info.classes[
						_index
					]
				);

				typedef
				fcppt::optional<
					sge::x11input::cursor::scroll_valuator_map::value_type
				>
				result_type;

				if(
					sge::x11input::device::info::class_type(
						cur
					)
					!=
					XIScrollClass
				)
					return
						result_type();

				XIScrollClassInfo const &scroll_class(
					sge::x11input::device::info::class_cast<
						XIScrollClassInfo const &
					>(
						cur
					)
				);

				sge::x11input::device::valuator::index const index{
					scroll_class.number
				};

				return
					result_type(
						std::make_pair(
							index,
							sge::x11input::cursor::scroll_valuator(
								sge::x11input::device::valuator::any{
									// For some reason the X server reports
									// relative valuators which are in fact absolute.
									// Use make_any when this is fixed.
									sge::x11input::device::valuator::make_absolute(
										sge::x11input::cursor::find_scroll_valuator(
											index,
											_info
										)
									)
								},
								sge::x11input::cursor::scroll_code(
									scroll_class.scroll_type
								)
							)
						)
					);
			}
		);
}
