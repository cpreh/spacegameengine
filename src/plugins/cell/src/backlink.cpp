#include "../backlink.hpp"
#include "../grid_entry.hpp"

sge::cell::backlink::backlink(
	grid_entry &entry_,
	circle_list::iterator const it)
:
	entry_(entry_),
	it(it)
{}

sge::cell::grid_entry &
sge::cell::backlink::entry()
{
	return entry_;
}

void sge::cell::backlink::unlink()
{
	entry_.entries().erase(
		it);
}
