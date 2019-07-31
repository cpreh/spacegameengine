//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/rucksack/axis.hpp>
#include <sge/rucksack/axis_policy.hpp>
#include <sge/rucksack/axis_policy2.hpp>
#include <fcppt/assert/unreachable.hpp>


sge::rucksack::axis_policy2::axis_policy2(
	sge::rucksack::axis_policy const &_x,
	sge::rucksack::axis_policy const &_y
)
:
	x_{
		_x
	},
	y_{
		_y
	}
{
}

sge::rucksack::axis_policy const &
sge::rucksack::axis_policy2::x() const
{
	return
		x_;
}

sge::rucksack::axis_policy const &
sge::rucksack::axis_policy2::y() const
{
	return
		y_;
}

sge::rucksack::axis_policy const &
sge::rucksack::axis_policy2::operator[](
	sge::rucksack::axis const _axis
) const
{
	switch(
		_axis
	)
	{
	case sge::rucksack::axis::x:
		return
			x_;
	case sge::rucksack::axis::y:
		return
			y_;
	}

	FCPPT_ASSERT_UNREACHABLE;
}
