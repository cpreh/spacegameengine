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


#include <sge/input/exception.hpp>
#include <sge/input/mouse/button_info_container.hpp>
#include <sge/x11input/device/info/class_maybe.hpp>
#include <sge/x11input/mouse/button_infos.hpp>
#include <sge/x11input/mouse/make_button_infos.hpp>
#include <awl/backends/x11/display_fwd.hpp>
#include <fcppt/make_int_range_count.hpp>
#include <fcppt/optional_bind_construct.hpp>
#include <fcppt/text.hpp>
#include <fcppt/algorithm/find_by_exn.hpp>
#include <fcppt/config/external_begin.hpp>
#include <X11/extensions/XInput2.h>
#include <fcppt/config/external_end.hpp>


sge::input::mouse::button_info_container
sge::x11input::mouse::make_button_infos(
	awl::backends::x11::display &_display,
	XIDeviceInfo const &_info
)
{
	return
		sge::input::mouse::button_info_container(
			fcppt::algorithm::find_by_exn(
				fcppt::make_int_range_count(
					_info.num_classes
				),
				[
					&_display,
					&_info
				](
					int const _index
				)
				{
					return
						fcppt::optional_bind_construct(
							sge::x11input::device::info::class_maybe<
								XIButtonClassInfo
							>(
								*_info.classes[
									_index
								]
							),
							[
								&_display
							](
								XIButtonClassInfo const &_button_class
							)
							{
								return
									sge::x11input::mouse::button_infos(
										_button_class,
										_display
									);
							}
						);
				},
				[]{
					return
						sge::input::exception{
							FCPPT_TEXT("No button class found")
						};
				}
			)
		);
}
