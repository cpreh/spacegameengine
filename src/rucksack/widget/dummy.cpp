/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2013 Carl Philipp Reh (sefi@s-e-f-i.de)

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

// TODO: Initialize position and size in the ctor?

sge::rucksack::widget::dummy::dummy(
	sge::rucksack::axis_policy2 const &_axis_policy)
:
	sge::rucksack::widget::base(
		widget::optional_parent()),
	axis_policy_(
		_axis_policy),
	position_(
		sge::rucksack::vector::null()),
	size_(
		sge::rucksack::dim::null())
{
}

void
sge::rucksack::widget::dummy::size(
	sge::rucksack::dim const &_size)
{
	size_ =
		_size;
}

void
sge::rucksack::widget::dummy::position(
	sge::rucksack::vector const &_position)
{
	position_ =
		_position;
}

sge::rucksack::dim const
sge::rucksack::widget::dummy::size() const
{
	return size_;
}

sge::rucksack::vector const
sge::rucksack::widget::dummy::position() const
{
	return position_;
}

sge::rucksack::axis_policy2 const
sge::rucksack::widget::dummy::axis_policy() const
{
	return axis_policy_;
}

void
sge::rucksack::widget::dummy::relayout()
{
}

sge::rucksack::widget::dummy::~dummy()
{
}
