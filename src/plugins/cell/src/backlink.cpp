#include "../backlink.hpp"
#include "../grid_entry.hpp"

sge::cell::backlink::backlink(
	grid_entry &entry_,
	cell::circle &circle_)
:
	entry_(&entry_),
	circle_(&circle_)
{}

sge::cell::grid_entry &
sge::cell::backlink::entry()
{
	return *entry_;
}

sge::cell::circle &
sge::cell::backlink::circle()
{
	return *circle_;
}
