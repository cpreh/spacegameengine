//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/x11input/cursor/find_scroll_valuator.hpp>
#include <sge/x11input/cursor/make_scroll_valuators.hpp>
#include <sge/x11input/cursor/scroll_code.hpp>
#include <sge/x11input/cursor/scroll_valuator.hpp>
#include <sge/x11input/cursor/scroll_valuator_map.hpp>
#include <sge/x11input/device/info/class_maybe.hpp>
#include <sge/x11input/device/valuator/index.hpp>
#include <sge/x11input/device/valuator/make_absolute.hpp>
#include <fcppt/make_int_range_count.hpp>
#include <fcppt/reference_impl.hpp>
#include <fcppt/algorithm/map_optional.hpp>
#include <fcppt/optional/map.hpp>
#include <fcppt/config/external_begin.hpp>
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
				return
					fcppt::optional::map(
						sge::x11input::device::info::class_maybe<
							XIScrollClassInfo
						>(
							*_info.classes[
								_index
							]
						),
						[
							&_info
						](
							fcppt::reference<
								XIScrollClassInfo const
							> const _scroll_class
						)
						{
							sge::x11input::device::valuator::index const index{
								_scroll_class.get().number
							};

							return
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
											_scroll_class.get().scroll_type
										)
									)
								);
						}
					);
			}
		);
}
