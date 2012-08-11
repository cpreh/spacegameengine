/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2012 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#include <sge/rucksack/widget/enumeration.hpp>
#include <fcppt/assert/pre.hpp>
#include <fcppt/config/external_begin.hpp>
#include <algorithm>
#include <fcppt/config/external_end.hpp>


sge::rucksack::widget::enumeration::enumeration(
	sge::rucksack::padding const &_padding,
	sge::rucksack::aspect const &_aspect)
:
	widget::base(
		widget::optional_parent()),
	padding_(
		_padding.get()),
	aspect_(
		_aspect),
	children_(),
	position_(),
	size_()
{
}

void
sge::rucksack::widget::enumeration::size(
	sge::rucksack::dim const &_size)
{
	size_ =
		_size;
}

void
sge::rucksack::widget::enumeration::position(
	sge::rucksack::vector const &_position)
{
	position_ =
		_position;
}

sge::rucksack::dim const
sge::rucksack::widget::enumeration::size() const
{
	return
		size_;
}

sge::rucksack::vector const
sge::rucksack::widget::enumeration::position() const
{
	return
		position_;
}

sge::rucksack::axis_policy2 const
sge::rucksack::widget::enumeration::axis_policy() const
{
	return
		sge::rucksack::axis_policy2(
			sge::rucksack::axis_policy(
				sge::rucksack::minimum_size(
					0),
				sge::rucksack::preferred_size(
					sge::rucksack::optional_scalar()),
				sge::rucksack::is_expanding(
					true)),
			sge::rucksack::axis_policy(
				sge::rucksack::minimum_size(
					0),
				sge::rucksack::preferred_size(
					sge::rucksack::optional_scalar()),
				sge::rucksack::is_expanding(
					true)),
			aspect_);
}

void
sge::rucksack::widget::enumeration::relayout()
{
	sge::rucksack::vector current_pos(
		this->position().x(),
		this->position().y() + padding_);

	sge::rucksack::scalar current_row_max_height =
		0;

	for(
		child_information::iterator child_ptr =
			children_.begin();
		child_ptr != children_.end();
		child_ptr++)
	{
		sge::rucksack::dim const preferred_or_minimum(
			(*child_ptr)->axis_policy().x().preferred_size()
			?
				*(*child_ptr)->axis_policy().x().preferred_size()
			:
				(*child_ptr)->axis_policy().x().minimum_size(),
			(*child_ptr)->axis_policy().y().preferred_size()
			?
				*(*child_ptr)->axis_policy().y().preferred_size()
			:
				(*child_ptr)->axis_policy().y().minimum_size());

		// Next line
		if(current_pos.x() + padding_ + preferred_or_minimum.w() > this->position().x() + this->size().w())
		{
			// This assertion makes sure that we have enough space
			// at the bottom. It's too strict, however, so I
			// uncommented it.
			//FCPPT_ASSERT_PRE(
			//	current_pos.y() + preferred_or_minimum.h() <= this->position().y() + this->size().h());
			current_pos.x() =
				this->position().x();

			current_pos.y() +=
				current_row_max_height + padding_;

			current_row_max_height =
				0;
		}

		(*child_ptr)->position(
			sge::rucksack::vector(
				current_pos.x() + padding_,
				current_pos.y()));

		(*child_ptr)->size(
			preferred_or_minimum);

		(*child_ptr)->relayout();

		current_pos.x() +=
			preferred_or_minimum.w() + padding_;

		current_row_max_height =
			std::max(
				current_row_max_height,
				preferred_or_minimum.h());
	}
}

void
sge::rucksack::widget::enumeration::push_back_child(
	widget::base &_child)
{
	children_.push_back(
		&_child);
	_child.parent(
		widget::optional_parent(
			*this));
}

sge::rucksack::widget::enumeration::~enumeration()
{
	for(
		child_information::iterator child_ptr =
			children_.begin();
		child_ptr != children_.end();
		child_ptr++)
		(*child_ptr)->parent(
			widget::optional_parent());
}

void
sge::rucksack::widget::enumeration::child_destroyed(
	widget::base &_child)
{
	child_information::iterator it =
		std::find(
			children_.begin(),
			children_.end(),
			&_child);

	FCPPT_ASSERT_PRE(
		it != children_.end());

	children_.erase(
		it);
}
