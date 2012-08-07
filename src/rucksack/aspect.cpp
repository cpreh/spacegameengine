#include <sge/rucksack/aspect.hpp>

sge::rucksack::aspect::aspect(
	sge::rucksack::scalar const _x,
	sge::rucksack::scalar const _y)
:
	x_(
		_x),
	y_(
		_y)
{
}

sge::rucksack::scalar
sge::rucksack::aspect::x() const
{
	return x_;
}

sge::rucksack::scalar
sge::rucksack::aspect::y() const
{
	return y_;
}
