#include <sge/rucksack/alignment2.hpp>

sge::rucksack::alignment2::alignment2(
	alignment::type const _x,
	alignment::type const _y)
:
	x_(
		_x),
	y_(
		_y)
{
}

sge::rucksack::alignment::type
sge::rucksack::alignment2::x() const
{
	return x_;
}

sge::rucksack::alignment::type
sge::rucksack::alignment2::y() const
{
	return y_;
}
