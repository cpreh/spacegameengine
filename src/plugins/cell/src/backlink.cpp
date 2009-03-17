#include "../backlink.hpp"
#include "../grid_entry.hpp"

sge::cell::backlink::backlink(
	grid_entry &entry_,
	cell::circle &circle_)
:
	entry_(&entry_),
	circle_(&circle_)
{}

sge::cell::backlink::backlink(
	backlink const &l)
:
	entry_(l.entry_),
	circle_(l.circle_)
{
	add_me();
}

sge::cell::backlink &
sge::cell::backlink::operator=(
	backlink const &l)
{
	if(&l == this)
		return *this;
	unlink();
	entry_ = l.entry_;
	circle_ = l.circle_;
	add_me();
	return *this;
}

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

void
sge::cell::backlink::add_me()
{
	entry().entries().push_back(
		*this
	);
}
