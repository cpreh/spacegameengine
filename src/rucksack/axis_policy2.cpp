#include <sge/rucksack/axis_policy2.hpp>

sge::rucksack::axis_policy2::axis_policy2(
	sge::rucksack::axis_policy const &_x,
	sge::rucksack::axis_policy const &_y,
	sge::rucksack::aspect const &_aspect)
:
	x_(
		_x),
	y_(
		_y),
	aspect_(
		_aspect)
{
}

sge::rucksack::axis_policy const &
sge::rucksack::axis_policy2::x() const
{
	return x_;
}

sge::rucksack::axis_policy const &
sge::rucksack::axis_policy2::y() const
{
	return y_;
}

sge::rucksack::axis_policy const &
sge::rucksack::axis_policy2::operator[](
	sge::rucksack::dim::size_type const i) const
{
	return i == 0 ? x_ : y_;
}

sge::rucksack::aspect const &
sge::rucksack::axis_policy2::aspect() const
{
	return aspect_;
}
