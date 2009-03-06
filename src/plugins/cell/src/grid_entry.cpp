#include "../grid_entry.hpp"

void
sge::cell::grid_entry::update(
	time::funit const delta)
{
	BOOST_FOREACH(
		weak_circle_list::reference r,
		refs
	)
	{
		r->update(
			delta
		);
	}
}
