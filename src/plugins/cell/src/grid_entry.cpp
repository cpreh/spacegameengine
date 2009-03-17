#include "../grid_entry.hpp"

sge::cell::grid_entry::grid_entry()
{}

sge::cell::grid_entry::grid_entry(
	grid_entry const &)
{}

sge::cell::grid_entry &
sge::cell::grid_entry::operator=(
	grid_entry const &)
{
	return *this;
}

sge::cell::intrusive_backlink_list &
sge::cell::grid_entry::entries()
{
	return entries_;
}
