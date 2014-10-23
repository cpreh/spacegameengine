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


#ifndef SGE_RUCKSACK_WIDGET_FRAME_HPP_INCLUDED
#define SGE_RUCKSACK_WIDGET_FRAME_HPP_INCLUDED

#include <sge/core/detail/class_symbol.hpp>
#include <sge/rucksack/axis_policy2_fwd.hpp>
#include <sge/rucksack/dim_fwd.hpp>
#include <sge/rucksack/padding.hpp>
#include <sge/rucksack/detail/symbol.hpp>
#include <sge/rucksack/vector_fwd.hpp>
#include <sge/rucksack/widget/base.hpp>
#include <fcppt/noncopyable.hpp>


namespace sge
{
namespace rucksack
{
namespace widget
{

class SGE_CORE_DETAIL_CLASS_SYMBOL frame
:
	public sge::rucksack::widget::base
{
	FCPPT_NONCOPYABLE(
		frame
	);
public:
	SGE_RUCKSACK_DETAIL_SYMBOL
	frame(
		sge::rucksack::widget::base &,
		sge::rucksack::padding
	);

	SGE_RUCKSACK_DETAIL_SYMBOL
	void
	size(
		sge::rucksack::dim const &
	)
	override;

	SGE_RUCKSACK_DETAIL_SYMBOL
	void
	position(
		sge::rucksack::vector const &
	)
	override;

	SGE_RUCKSACK_DETAIL_SYMBOL
	sge::rucksack::dim const
	size() const
	override;

	SGE_RUCKSACK_DETAIL_SYMBOL
	sge::rucksack::vector const
	position() const
	override;

	SGE_RUCKSACK_DETAIL_SYMBOL
	sge::rucksack::axis_policy2 const
	axis_policy() const
	override;

	SGE_RUCKSACK_DETAIL_SYMBOL
	void
	relayout()
	override;

	SGE_RUCKSACK_DETAIL_SYMBOL
	~frame()
	override;

	SGE_RUCKSACK_DETAIL_SYMBOL
	sge::rucksack::padding const
	padding() const;
private:
	sge::rucksack::vector const
	shifted_position() const;

	sge::rucksack::dim const
	extra_size() const;

	sge::rucksack::widget::base &child_;

	sge::rucksack::padding const padding_;
};

}
}
}

#endif
