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


#ifndef SGE_RUCKSACK_WIDGET_ENUMERATION_HPP_INCLUDED
#define SGE_RUCKSACK_WIDGET_ENUMERATION_HPP_INCLUDED

#include <sge/rucksack/axis_policy2_fwd.hpp>
#include <sge/rucksack/dim.hpp>
#include <sge/rucksack/padding_fwd.hpp>
#include <sge/rucksack/scalar.hpp>
#include <sge/rucksack/vector.hpp>
#include <sge/rucksack/widget/base.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/config/external_begin.hpp>
#include <vector>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace rucksack
{
namespace widget
{
/**
 * The enumeration widget starts aligning its child widgets from left to right
 * until there's no more space on the right. Then, it creates a new row and
 * again, aligns from the left to right (like a word processor does with words).
 */
class enumeration
:
	public sge::rucksack::widget::base
{
FCPPT_NONCOPYABLE(
	enumeration);
public:
	SGE_RUCKSACK_SYMBOL
	explicit
	enumeration(
		sge::rucksack::padding const &
	);

	SGE_RUCKSACK_SYMBOL
	void
	size(
		sge::rucksack::dim const &
	)
	override;

	SGE_RUCKSACK_SYMBOL
	void
	position(
		sge::rucksack::vector const &
	)
	override;

	SGE_RUCKSACK_SYMBOL
	sge::rucksack::dim const
	size() const
	override;

	SGE_RUCKSACK_SYMBOL
	sge::rucksack::vector const
	position() const
	override;

	SGE_RUCKSACK_SYMBOL
	sge::rucksack::axis_policy2 const
	axis_policy() const
	override;

	SGE_RUCKSACK_SYMBOL
	void
	relayout()
	override;

	SGE_RUCKSACK_SYMBOL
	void
	push_back_child(
		sge::rucksack::widget::base &
	);

	SGE_RUCKSACK_SYMBOL
	~enumeration()
	override;
private:
	typedef
	std::vector<sge::rucksack::widget::base*>
	child_information;

	sge::rucksack::scalar const padding_;
	child_information children_;
	sge::rucksack::vector position_;
	sge::rucksack::dim size_;

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
