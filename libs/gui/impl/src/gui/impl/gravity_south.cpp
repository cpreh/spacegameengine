//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/gui/gravity.hpp>
#include <sge/gui/impl/gravity_south.hpp>
#include <fcppt/assert/unreachable.hpp>


bool
sge::gui::impl::gravity_south(
	sge::gui::gravity const _gravity
)
{
	switch(
		_gravity
	)
	{
		case sge::gui::gravity::north_east:
		case sge::gui::gravity::north_west:
			return
				false;
		case sge::gui::gravity::south_east:
		case sge::gui::gravity::south_west:
			return
				true;
	}

	FCPPT_ASSERT_UNREACHABLE;
}
