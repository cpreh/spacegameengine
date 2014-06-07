/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2014 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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


#include <sge/rucksack/rect.hpp>
#include <sge/rucksack/widget/base.hpp>
#include <sge/rucksack/widget/optional_parent.hpp>


sge::rucksack::widget::base::~base()
{
	if(parent_)
		parent_->child_destroyed(
			*this);
}

sge::rucksack::widget::base::base(
	sge::rucksack::widget::optional_parent const &_parent)
:
	parent_(
		_parent)
{
}

sge::rucksack::rect const
sge::rucksack::widget::base::area() const
{
	return
		sge::rucksack::rect(
			this->position(),
			this->size());
}

void
sge::rucksack::widget::base::parent(
	sge::rucksack::widget::optional_parent const &_parent)
{
	parent_ = _parent;
}

sge::rucksack::widget::optional_parent const &
sge::rucksack::widget::base::parent() const
{
	return parent_;
}

void
sge::rucksack::widget::base::child_destroyed(
	base &)
{
}
