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


#include <sge/rucksack/optional_scalar.hpp>
#include <sge/rucksack/widget/box/base.hpp>
#include <fcppt/text.hpp>
#include <fcppt/assert/pre.hpp>
#include <fcppt/assert/unreachable.hpp>
#include <fcppt/io/clog.hpp>
#include <fcppt/config/external_begin.hpp>
#include <algorithm>
#include <vector>
#include <fcppt/config/external_end.hpp>


sge::rucksack::widget::box::base::base(
	sge::rucksack::axis::type const _axis,
	sge::rucksack::aspect const &_aspect)
:
	widget::base(
		widget::optional_parent()),
	children_(),
	axis_(
		// For an explanation, see the header
		static_cast<sge::rucksack::dim::size_type>(
			_axis)),
	aspect_(
		_aspect),
	// We cannot initialize position and size to something meaningful yet, so
	// keep uninitialized
	position_(),
	size_()
{
}

void
sge::rucksack::widget::box::base::size(
	sge::rucksack::dim const &_size)
{
	size_ =
		_size;
}

void
sge::rucksack::widget::box::base::position(
	sge::rucksack::vector const &_position)
{
	position_ =
		_position;
}

sge::rucksack::dim const
sge::rucksack::widget::box::base::size() const
{
	return size_;
}

sge::rucksack::vector const
sge::rucksack::widget::box::base::position() const
{
	return position_;
}

sge::rucksack::axis_policy2 const
sge::rucksack::widget::box::base::axis_policy() const
{
	sge::rucksack::scalar
		minimum_size_minor =
			0,
		minimum_size_major =
			0;

	sge::rucksack::scalar
		preferred_size_minor =
			0,
		preferred_size_major =
			0;

	bool
		is_expanding_minor =
			false,
		is_expanding_major =
			false;

	for(
		child_information::const_iterator child_and_information_pair_it =
			children_.begin();
		child_and_information_pair_it != children_.end();
		++child_and_information_pair_it)
	{
		// Less to type with these three variables :)
		sge::rucksack::axis_policy2 const this_axis_policy =
			child_and_information_pair_it->first->axis_policy();

		sge::rucksack::axis_policy const
			minor_policy =
				this_axis_policy[this->minor_axis()],
			major_policy =
				this_axis_policy[this->major_axis()];

		// Minimum size
		minimum_size_major +=
			major_policy.minimum_size();

		minimum_size_minor =
			std::max(
				minimum_size_minor,
				minor_policy.minimum_size());

		// Preferred size (forward to minimum size if preferred not available)
		preferred_size_major +=
			major_policy.preferred_size()
			?
				*(major_policy.preferred_size())
			:
				major_policy.minimum_size();

		preferred_size_minor =
			std::max(
				preferred_size_minor,
				minor_policy.preferred_size()
				?
					*(minor_policy.preferred_size())
				:
					minor_policy.minimum_size());

		// Is expanding.
		is_expanding_minor |=
			minor_policy.is_expanding();

		is_expanding_major |=
			major_policy.is_expanding();
	}

	sge::rucksack::axis_policy const
		minor_policy(
			(sge::rucksack::minimum_size(
				minimum_size_minor)),
			sge::rucksack::preferred_size(
				sge::rucksack::optional_scalar(
					preferred_size_minor)),
			sge::rucksack::is_expanding(
				is_expanding_minor)),
		major_policy(
			(sge::rucksack::minimum_size(
				minimum_size_major)),
			sge::rucksack::preferred_size(
				sge::rucksack::optional_scalar(
					preferred_size_major)),
			sge::rucksack::is_expanding(
				is_expanding_major));

	// Note that the axis policy doesn't differentiate with "minor" and "major"
	// but with "x" and "y", so we have to map it here.
	return
		sge::rucksack::axis_policy2(
			axis_ == 0
			?
				major_policy
			:
			minor_policy,
			axis_ == 0
			?
				minor_policy
			:
				major_policy,
			aspect_);
}

void
sge::rucksack::widget::box::base::relayout()
{
	if(children_.empty())
		return;

	this->relayout_major_axis();
	this->relayout_minor_axis();

	// Now that we have all the sizes, let's update the widgets and set a
	// position, too.
	// For the position, we first see how much space we have left in the widget
	sge::rucksack::scalar remaining = this->size()[this->major_axis()];
	for(
		child_information::const_iterator widget_ptr_information_pair_it =
			children_.begin();
		widget_ptr_information_pair_it != children_.end();
		++widget_ptr_information_pair_it)
		remaining -= widget_ptr_information_pair_it->second.size()[this->major_axis()];

	// We have
	//
	// child_widgets + 1
	//
	// holes between the widgets. We distribute the extra space in "remaining"
	// uniformly to these holes.
	sge::rucksack::scalar const hole_size =
			remaining / static_cast<sge::rucksack::scalar>(children_.size()+1u);

	// This variable keeps track of the current "running" position on the major
	// axis. Note that the rectangles have absolute positioning, so we have to
	// add the outer rectangle's position on top of everything.
	sge::rucksack::scalar current_major_position =
		this->position()[this->major_axis()] + hole_size;

	for(
		child_information::const_iterator widget_ptr_information_pair_it =
			children_.begin();
		widget_ptr_information_pair_it != children_.end();
		++widget_ptr_information_pair_it)
	{
		widget_ptr_information_pair_it->first->size(
			widget_ptr_information_pair_it->second.size());

		sge::rucksack::vector new_position;
		// This time, the major axis is easy: Just set it to the "current" position.
		new_position[this->major_axis()] =
			current_major_position;

		// The minor axis is determined by the alignment parameter.
		switch(widget_ptr_information_pair_it->second.alignment())
		{
			case alignment::left_or_top:
				new_position[this->minor_axis()] =
					this->position()[this->minor_axis()];
				break;
			case alignment::center:
				// outer rectangle's left + outer rectangle's size/2 - inner rectangle's size/2 => center alignment
				new_position[this->minor_axis()] =
					this->position()[this->minor_axis()] +
					this->size()[this->minor_axis()]/2 -
					widget_ptr_information_pair_it->second.size()[this->minor_axis()]/2;
				break;
			case alignment::right_or_bottom:
				new_position[this->minor_axis()] =
					// outer rectangle's right - widget's size => right alignment
					this->position()[this->minor_axis()] +
					this->size()[this->minor_axis()] -
					widget_ptr_information_pair_it->second.size()[this->minor_axis()];
				break;
			case alignment::size:
				FCPPT_ASSERT_UNREACHABLE;
		}

		widget_ptr_information_pair_it->first->position(
			new_position);

		widget_ptr_information_pair_it->first->relayout();

		current_major_position +=
			hole_size +
			widget_ptr_information_pair_it->second.size()[this->major_axis()];
	}
}

void
sge::rucksack::widget::box::base::push_back_child(
	widget::base &_new_child,
	sge::rucksack::alignment::type const _alignment)
{
	children_.push_back(
		std::make_pair(
			&_new_child,
			box::child_information(
				_alignment,
				sge::rucksack::dim())));

	_new_child.parent(
		widget::optional_parent(
			*this));
}

void
sge::rucksack::widget::box::base::push_front_child(
	widget::base &_new_child,
	sge::rucksack::alignment::type const _alignment)
{
	children_.push_front(
		std::make_pair(
			&_new_child,
			box::child_information(
				_alignment,
				sge::rucksack::dim())));

	_new_child.parent(
		widget::optional_parent(
			*this));
}

void
sge::rucksack::widget::box::base::pop_front_child()
{
	children_.front().first->parent(
		widget::optional_parent());
	children_.pop_front();
}

sge::rucksack::widget::box::base::~base()
{
	for(
		child_information::iterator widget_ptr_information_pair_it =
			children_.begin();
		widget_ptr_information_pair_it != children_.end();
		++widget_ptr_information_pair_it)
		widget_ptr_information_pair_it->first->parent(
			widget::optional_parent());
}

sge::rucksack::dim::size_type
sge::rucksack::widget::box::base::major_axis() const
{
	return axis_;
}

sge::rucksack::dim::size_type
sge::rucksack::widget::box::base::minor_axis() const
{
	return
		static_cast<sge::rucksack::dim::size_type>(
			1u - axis_);
}

void
sge::rucksack::widget::box::base::relayout_major_axis()
{
	// First order of business: Assign each widget its minimum size on both axes.
	// Also, keep track of how much we've assigned in total on the major axis.
	// This is the basis for the corrections later on.
	sge::rucksack::scalar
		allocated_major_size =
			0;

	for(
		child_information::iterator widget_ptr_information_pair_it =
			children_.begin();
		widget_ptr_information_pair_it != children_.end();
		++widget_ptr_information_pair_it)
	{
		// FIXME: Recognize aspect here!
		widget_ptr_information_pair_it->second.size(
			sge::rucksack::dim(
				axis_ == 0
				?
					widget_ptr_information_pair_it->first->axis_policy()[this->major_axis()].minimum_size()
				:
					widget_ptr_information_pair_it->first->axis_policy()[this->minor_axis()].minimum_size(),
				axis_ == 0
				?
					widget_ptr_information_pair_it->first->axis_policy()[this->minor_axis()].minimum_size()
				:
					widget_ptr_information_pair_it->first->axis_policy()[this->major_axis()].minimum_size()));

		allocated_major_size +=
			widget_ptr_information_pair_it->first->axis_policy()[this->major_axis()].minimum_size();
	}

	// How much space do we have remaining on the major axis?
	sge::rucksack::scalar remaining =
		this->size()[this->major_axis()] - allocated_major_size;

	if(remaining < 0)
	{
//		fcppt::io::clog() << FCPPT_TEXT("The minimum size of all widgets together is ") << remaining << FCPPT_TEXT(" pixels too large!\n");
		return;
	}

	// We need the widgets which have a preferred size on the major axis
	typedef
	std::vector<widget::base *>
	widget_ptr_container;

	widget_ptr_container widgets_with_preferred_size;

	sge::rucksack::scalar additional_pixels =
		0;

	// Here we iterate over all children and memorize two things:
	//
	// 1. The widgets that have a preferred size (and whose preferred size is not
	//    equal to the minimum size).
	// 2. How much more pixels are needed to push each widget to the preferred
	//    size.
	for(
		child_information::const_iterator widget_ptr_information_pair_it =
			children_.begin();
		widget_ptr_information_pair_it != children_.end();
		++widget_ptr_information_pair_it)
	{
		// FIXME: Check if this widget has a preferered size and _CAN_ be resized
		// considering its height and aspect
		if(!widget_ptr_information_pair_it->first->axis_policy()[this->major_axis()].preferred_size())
			continue;

		sge::rucksack::scalar const size_difference =
			(*widget_ptr_information_pair_it->first->axis_policy()[this->major_axis()].preferred_size()) -
			widget_ptr_information_pair_it->first->axis_policy()[this->major_axis()].minimum_size();

		FCPPT_ASSERT_PRE(
			size_difference >= 0);

		if(size_difference == 0)
			continue;

		widgets_with_preferred_size.push_back(
			widget_ptr_information_pair_it->first);

		additional_pixels +=
			size_difference;
	}

	if(!widgets_with_preferred_size.empty())
	{
		// We have enough space left to increase the size of each widget to the preferred size. Great!
		if(remaining >= additional_pixels)
		{
			for(
				widget_ptr_container::const_iterator child_ptr =
					widgets_with_preferred_size.begin();
				child_ptr != widgets_with_preferred_size.end();
				++child_ptr)
			{
				sge::rucksack::dim current_size =
					this->information_for_ptr(*child_ptr).size();

				current_size[axis_] =
					*((*child_ptr)->axis_policy()[this->major_axis()].preferred_size());

				this->information_for_ptr(*child_ptr).size(
					current_size);
			}

			remaining -= additional_pixels;
		}
		else
		{
			// We don't have enough room, so partition the remaining space uniformly
			// among the widgets. Note that here, we _could_ partition according to
			// which widget is farthest away from its preferred size, but that's
			// overkill.
			for(
				widget_ptr_container::const_iterator child_ptr =
					widgets_with_preferred_size.begin();
				child_ptr != widgets_with_preferred_size.end();
				++child_ptr)
			{
				sge::rucksack::dim current_size =
					this->information_for_ptr(*child_ptr).size();

				sge::rucksack::scalar const preferred_size =
					*((*child_ptr)->axis_policy()[this->major_axis()].preferred_size());

				// Don't make it bigger than the preferred size
				current_size[axis_] =
					std::min(
						current_size[axis_] + remaining / static_cast<sge::rucksack::scalar>(widgets_with_preferred_size.size()),
						preferred_size);

				remaining -=
					current_size[axis_] - (*child_ptr)->axis_policy()[this->major_axis()].minimum_size();

				this->information_for_ptr(*child_ptr).size(
					current_size);
			}
		}
	}

	// After that step, we might have some room left
	if(remaining <= 0)
		return;

	// This step is the easiest: If we have space left, distribute it uniformly
	// among all widgets that can expand.
	widget_ptr_container widgets_which_expand;

	for(
		child_information::const_iterator widget_ptr_information_pair_it =
			children_.begin();
		widget_ptr_information_pair_it != children_.end();
		++widget_ptr_information_pair_it)
		// FIXME: Check if this widget has is expandable and _CAN_ be expanded
		// considering its height and aspect
		if(widget_ptr_information_pair_it->first->axis_policy()[this->major_axis()].is_expanding())
			widgets_which_expand.push_back(
				widget_ptr_information_pair_it->first);

	if(!widgets_which_expand.empty())
	{
		for(
			widget_ptr_container::const_iterator child_ptr =
				widgets_which_expand.begin();
			child_ptr != widgets_which_expand.end();
			++child_ptr)
		{
			sge::rucksack::dim current_size =
				this->information_for_ptr(*child_ptr).size();

			current_size[axis_] +=
				remaining / static_cast<sge::rucksack::scalar>(widgets_which_expand.size());

			this->information_for_ptr(*child_ptr).size(
				current_size);
		}
	}
}

void
sge::rucksack::widget::box::base::relayout_minor_axis()
{
	// Layouting the minor axis is pretty simple:
	// If the widget has a preferred size, take:
	//
	// min(preferred_size,height)
	//
	// As the height
	//
	// FIXME: ASPECT!
	for(
		child_information::iterator widget_ptr_information_pair_it =
			children_.begin();
		widget_ptr_information_pair_it != children_.end();
		++widget_ptr_information_pair_it)
	{
		sge::rucksack::dim current_size =
			widget_ptr_information_pair_it->second.size();

		bool const
			is_expanding =
				widget_ptr_information_pair_it->first->axis_policy()[this->minor_axis()].is_expanding(),
			has_preferred_size =
				widget_ptr_information_pair_it->first->axis_policy()[this->minor_axis()].preferred_size();

		if(is_expanding && !has_preferred_size)
		{
			current_size[this->minor_axis()] =
				this->size()[this->minor_axis()];
		}
		else if(has_preferred_size)
		{
			current_size[this->minor_axis()] =
				std::min(
					this->size()[this->minor_axis()],
					*widget_ptr_information_pair_it->first->axis_policy()[this->minor_axis()].preferred_size());
		}

		widget_ptr_information_pair_it->second.size(
			current_size);
	}
}

void
sge::rucksack::widget::box::base::child_destroyed(
	widget::base &_child)
{
	for(
		child_information::iterator widget_ptr_information_pair_it =
			children_.begin();
		widget_ptr_information_pair_it != children_.end();
		++widget_ptr_information_pair_it)
	{
		if(widget_ptr_information_pair_it->first == &_child)
		{
			children_.erase(
				widget_ptr_information_pair_it);
			return;
		}
	}

	FCPPT_ASSERT_UNREACHABLE;
}

sge::rucksack::widget::box::child_information &
sge::rucksack::widget::box::base::information_for_ptr(
	widget::base const * const ptr)
{
	for(
		child_information::iterator widget_ptr_information_pair_it =
			children_.begin();
		widget_ptr_information_pair_it != children_.end();
		++widget_ptr_information_pair_it)
	{
		if(widget_ptr_information_pair_it->first == ptr)
			return widget_ptr_information_pair_it->second;
	}

	FCPPT_ASSERT_UNREACHABLE;
}
