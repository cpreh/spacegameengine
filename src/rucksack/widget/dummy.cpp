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


#include <sge/rucksack/axis_policy2.hpp>
#include <sge/rucksack/dim.hpp>
#include <sge/rucksack/vector.hpp>
#include <sge/rucksack/widget/base.hpp>
#include <sge/rucksack/widget/dummy.hpp>
#include <fcppt/math/dim/null.hpp>
#include <fcppt/math/vector/null.hpp>


sge::rucksack::widget::dummy::dummy(
	sge::rucksack::axis_policy2 const &_axis_policy)
:
	sge::rucksack::widget::base(),
	axis_policy_{
		_axis_policy
	},
	position_{
		fcppt::math::vector::null<
			sge::rucksack::vector
		>()
	},
	size_{
		fcppt::math::dim::null<
			sge::rucksack::dim
		>()
	}
{
}

void
sge::rucksack::widget::dummy::size(
	sge::rucksack::dim const &_size
)
{
	size_ =
		_size;
}

void
sge::rucksack::widget::dummy::position(
	sge::rucksack::vector const &_position
)
{
	position_ =
		_position;
}

void
sge::rucksack::widget::dummy::axis_policy(
	sge::rucksack::axis_policy2 const &_axis_policy
)
{
	axis_policy_ =
		_axis_policy;
}

sge::rucksack::dim
sge::rucksack::widget::dummy::size() const
{
	return
		size_;
}

sge::rucksack::vector
sge::rucksack::widget::dummy::position() const
{
	return
		position_;
}

sge::rucksack::axis_policy2
sge::rucksack::widget::dummy::axis_policy() const
{
	return
		axis_policy_;
}

void
sge::rucksack::widget::dummy::relayout()
{
}

sge::rucksack::widget::dummy::~dummy()
{
}
