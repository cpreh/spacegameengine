/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2015 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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


#ifndef SGE_RUCKSACK_WIDGET_BOX_HPP_INCLUDED
#define SGE_RUCKSACK_WIDGET_BOX_HPP_INCLUDED

#include <sge/core/detail/class_symbol.hpp>
#include <sge/rucksack/alignment.hpp>
#include <sge/rucksack/axis.hpp>
#include <sge/rucksack/axis_policy2_fwd.hpp>
#include <sge/rucksack/dim.hpp>
#include <sge/rucksack/padding.hpp>
#include <sge/rucksack/vector.hpp>
#include <sge/rucksack/detail/symbol.hpp>
#include <sge/rucksack/widget/base.hpp>
#include <sge/rucksack/widget/reference.hpp>
#include <sge/rucksack/widget/reference_alignment_container.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/config/external_begin.hpp>
#include <list>
#include <utility>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace rucksack
{
namespace widget
{

/**
\brief Align child widgets next to each other in a box.
\details
The box class behaves just like the Qt box layout. It aligns its children
either vertically or horizontally (determined by the "axis" parameter which
specifies the "major axis" of alignment; hozirontal alignment has axis::x,
vertical has axis::y).
*/
class SGE_CORE_DETAIL_CLASS_SYMBOL box
:
	public
		sge::rucksack::widget::base
{
	FCPPT_NONCOPYABLE(
		box
	);

	typedef
	std::pair<
		sge::rucksack::widget::reference,
		sge::rucksack::alignment
	>
	child_pair;

	typedef
	std::list<
		child_pair
	>
	child_list;
public:
	SGE_RUCKSACK_DETAIL_SYMBOL
	box(
		sge::rucksack::axis,
		sge::rucksack::padding
	);

	SGE_RUCKSACK_DETAIL_SYMBOL
	box(
		sge::rucksack::axis,
		sge::rucksack::padding,
		sge::rucksack::widget::reference_alignment_container const &
	);

	// Nothing fancy, just set the stored size (this should NOT cause a relayout
	// immediately)
	SGE_RUCKSACK_DETAIL_SYMBOL
	void
	size(
		sge::rucksack::dim const &
	)
	override;

	using sge::rucksack::widget::base::size;

	// Nothing fancy, just set the stored position (this should NOT cause a
	// relayout immediately)
	SGE_RUCKSACK_DETAIL_SYMBOL
	void
	position(
		sge::rucksack::vector const &
	)
	override;

	using sge::rucksack::widget::base::position;

	// Nothing fancy, just return the stored size
	SGE_RUCKSACK_DETAIL_SYMBOL
	sge::rucksack::dim
	size() const
	override;

	// Nothing fancy, just return the stored position
	SGE_RUCKSACK_DETAIL_SYMBOL
	sge::rucksack::vector
	position() const
	override;

	// We have to calculate/set:
	//
	// 1. The minimum size (for each axis)
	// 2. The preferred size (for each axis)
	// 3. If the widget is expandable (for each axis)
	// 4. Aspect
	//
	// The minimum size for the _major_ axis is easy: We just accumulate the
	// minimum sizes of all the children.
	//
	// The minimum size of the _minor_ axis is equally simple: Take the maximum
	// of all the children's sizes.
	//
	// For the preferred size, we forward to the minimum size if the preferred
	// size is not given. If it _is_ given, we do the same as in the minimum
	// case, just with "preferred" instead of "minimum".
	//
	// Finally, the widget is expandable on each axis if there's at least one
	// widget that's expandable.
	//
	// Also note that currently, box widgets always have a preferred size (which
	// might be equal to the minimum size).
	SGE_RUCKSACK_DETAIL_SYMBOL
	sge::rucksack::axis_policy2
	axis_policy() const
	override;

	// This does a lot of stuff, see the code itself.
	SGE_RUCKSACK_DETAIL_SYMBOL
	void
	relayout()
	override;

	SGE_RUCKSACK_DETAIL_SYMBOL
	void
	push_back_child(
		sge::rucksack::widget::base &,
		sge::rucksack::alignment
	);

	SGE_RUCKSACK_DETAIL_SYMBOL
	void
	push_front_child(
		sge::rucksack::widget::base &,
		sge::rucksack::alignment
	);

	SGE_RUCKSACK_DETAIL_SYMBOL
	void
	pop_back_child();

	SGE_RUCKSACK_DETAIL_SYMBOL
	void
	pop_front_child();

	SGE_RUCKSACK_DETAIL_SYMBOL
	void
	clear();

	typedef
	child_list::iterator
	iterator;

	typedef
	child_list::size_type
	size_type;

	SGE_RUCKSACK_DETAIL_SYMBOL
	iterator
	child_position(
		size_type
	);

	SGE_RUCKSACK_DETAIL_SYMBOL
	size_type
	children_size() const;

	SGE_RUCKSACK_DETAIL_SYMBOL
	void
	replace_children(
		iterator,
		sge::rucksack::widget::base &,
		sge::rucksack::alignment
	);

	SGE_RUCKSACK_DETAIL_SYMBOL
	~box()
	override;
private:
	void
	insert_child(
		iterator,
		sge::rucksack::widget::base &,
		sge::rucksack::alignment
	);

	iterator
	erase_child(
		iterator
	);

	child_list children_;

	sge::rucksack::axis const axis_;

	sge::rucksack::padding const padding_;

	sge::rucksack::vector position_;

	sge::rucksack::dim size_;

	sge::rucksack::axis
	major_axis() const;

	sge::rucksack::axis
	minor_axis() const;

	void
	child_destroyed(
		sge::rucksack::widget::base &
	)
	override;
};

}
}
}

#endif
