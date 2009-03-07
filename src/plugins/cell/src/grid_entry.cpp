#include "../grid_entry.hpp"
#include "../circle.hpp"
#include <boost/foreach.hpp>

void
sge::cell::grid_entry::update(
	collision::time_unit const delta)
{
	BOOST_FOREACH(
		circle_list::reference r,
		entries_	
	)
	{
		r->update(
			delta
		);
	}
}

sge::cell::circle_list &
sge::cell::grid_entry::entries()
{
	return entries_;
}
