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


#include <sge/rucksack/alignment.hpp>
#include <sge/rucksack/dim.hpp>
#include <sge/rucksack/widget/box/child_information.hpp>


sge::rucksack::widget::box::child_information::child_information(
	sge::rucksack::alignment const _alignment,
	sge::rucksack::dim const &_size)
:
	alignment_(
		_alignment),
	size_(
		_size)
{
}

sge::rucksack::alignment
sge::rucksack::widget::box::child_information::alignment() const
{
	return alignment_;
}

sge::rucksack::dim const &
sge::rucksack::widget::box::child_information::size() const
{
	return size_;
}

void
sge::rucksack::widget::box::child_information::size(
	sge::rucksack::dim const &_size)
{
	size_ =
		_size;
}
