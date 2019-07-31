//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/input/cursor/position.hpp>
#include <sge/input/cursor/position_unit.hpp>
#include <sge/wlinput/cursor/position.hpp>
#include <fcppt/config/external_begin.hpp>
#include <wayland-util.h>
#include <fcppt/config/external_end.hpp>


sge::input::cursor::position
sge::wlinput::cursor::position(
	wl_fixed_t const _x,
	wl_fixed_t const _y
)
{
	auto const convert(
		[](
			wl_fixed_t const _val
		)
		->
		sge::input::cursor::position_unit
		{
			return
				::wl_fixed_to_int(
					_val
				);
		}
	);

	return
		sge::input::cursor::position{
			convert(
				_x
			),
			convert(
				_y
			)
		};
}
