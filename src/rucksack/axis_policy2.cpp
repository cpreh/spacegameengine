/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2016 Carl Philipp Reh (carlphilippreh <at> gmail.com)

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU Lesser General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
*/


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
