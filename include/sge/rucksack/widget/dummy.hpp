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


#ifndef SGE_RUCKSACK_WIDGET_DUMMY_HPP_INCLUDED
#define SGE_RUCKSACK_WIDGET_DUMMY_HPP_INCLUDED

#include <sge/rucksack/axis_policy2.hpp>
#include <sge/rucksack/dim.hpp>
#include <sge/rucksack/symbol.hpp>
#include <sge/rucksack/vector.hpp>
#include <sge/rucksack/widget/base.hpp>
#include <fcppt/noncopyable.hpp>


namespace sge
{
namespace rucksack
{
namespace widget
{

class dummy
:
	public sge::rucksack::widget::base
{
	FCPPT_NONCOPYABLE(
		dummy
	);
public:
	SGE_RUCKSACK_SYMBOL
	explicit
	dummy(
		sge::rucksack::axis_policy2 const &
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
	void
	axis_policy(
		sge::rucksack::axis_policy2 const &
	);

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
	~dummy()
	override;
private:
	sge::rucksack::axis_policy2 axis_policy_;

	sge::rucksack::vector position_;

	sge::rucksack::dim size_;
};

}
}
}

#endif
