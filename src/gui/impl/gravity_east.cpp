#include <sge/gui/gravity.hpp>
#include <sge/gui/impl/gravity_east.hpp>
#include <fcppt/assert/unreachable.hpp>


bool
sge::gui::impl::gravity_east(
	sge::gui::gravity const _gravity
)
{
	switch(
		_gravity
	)
	{
		case sge::gui::gravity::north_west:
		case sge::gui::gravity::south_west:
			return
				false;
		case sge::gui::gravity::south_east:
		case sge::gui::gravity::north_east:
			return
				true;
	}

	FCPPT_ASSERT_UNREACHABLE;
}
