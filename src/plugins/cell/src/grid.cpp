#include "../grid.hpp"
#include "../grid_entry.hpp"
#include <sge/math/dim/basic_impl.hpp>
#include <sge/math/dim/arithmetic.hpp>
#include <sge/structure_cast.hpp>
#include <boost/foreach.hpp>

sge::cell::grid::grid(
	collision::rect const &rect_)
:
	rect_(rect_)
{
}

void
sge::cell::grid::update(
	time::funit const delta)
{
	BOOST_FOREACH(
		field_type::reference r,
		field_
	)
		r.update(
			delta);
}

sge::cell::field_type &
sge::cell::grid::field()
{
	return field_;
}

sge::cell::grid::dim_type const
sge::cell::grid::cell_size() const
{
	return rect_.dim()
	/ structure_cast<
		dim_type
	>(
		field_.dim()
	);
}
