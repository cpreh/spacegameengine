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
