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
#include <sge/x11input/cursor/find_scroll_valuator.hpp>
#include <sge/x11input/device/info/class_maybe.hpp>
#include <sge/x11input/device/valuator/index.hpp>
#include <fcppt/make_int_range_count.hpp>
#include <fcppt/reference_impl.hpp>
#include <fcppt/text.hpp>
#include <fcppt/algorithm/find_by_opt.hpp>
#include <fcppt/optional/bind.hpp>
#include <fcppt/optional/reference.hpp>
#include <fcppt/optional/to_exception.hpp>
#include <fcppt/config/external_begin.hpp>
#include <X11/extensions/XInput2.h>
#include <fcppt/config/external_end.hpp>


XIValuatorClassInfo const &
sge::x11input::cursor::find_scroll_valuator(
	sge::x11input::device::valuator::index const _number,
	XIDeviceInfo const &_info
)
{
	return
		fcppt::optional::to_exception(
			fcppt::algorithm::find_by_opt(
				fcppt::make_int_range_count(
					_info.num_classes
				),
				[
					_number,
					&_info
				](
					int const _index
				)
				{
					return
						fcppt::optional::bind(
							sge::x11input::device::info::class_maybe<
								XIValuatorClassInfo
							>(
								*_info.classes[
									_index
								]
							),
							[
								_number
							](
								fcppt::reference<
									XIValuatorClassInfo const
								> const _valuator_class
							)
							{
								typedef
								fcppt::optional::reference<
									XIValuatorClassInfo const
								>
								result_type;

								return
									_valuator_class.get().number
									==
									_number.get()
									?
										result_type(
											_valuator_class
										)
									:
										result_type()
									;
							}
						);
				}
			),
			[]{
				return
					sge::input::exception{
						FCPPT_TEXT("Scroll valuator not present")
					};
			}
		).get();
}
