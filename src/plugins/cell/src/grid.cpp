#include "../grid.hpp"

void
sge::cell::grid::update(
	time::funit const delta)
{
	BOOST_FOREACH(
		field_type::reference r,
		field
	)
		r.update(
			delta);
}
