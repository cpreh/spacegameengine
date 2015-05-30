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


#ifndef SGE_RUCKSACK_WIDGET_MASTER_AND_SLAVES_HPP_INCLUDED
#define SGE_RUCKSACK_WIDGET_MASTER_AND_SLAVES_HPP_INCLUDED

#include <sge/core/detail/class_symbol.hpp>
#include <sge/rucksack/axis_policy2_fwd.hpp>
#include <sge/rucksack/dim.hpp>
#include <sge/rucksack/padding_fwd.hpp>
#include <sge/rucksack/vector.hpp>
#include <sge/rucksack/detail/symbol.hpp>
#include <sge/rucksack/widget/base.hpp>
#include <sge/rucksack/widget/box.hpp>
#include <sge/rucksack/widget/enumeration.hpp>
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
 * The master and slaves widget is a pretty "special" one. Chances are you
 * don't need it.
 *
 * The widget has a "master widget" and multiple "subwidgets". The master
 * widget is displayed in a column on the left, the subwidgets are displayed on the right
 */
class SGE_CORE_DETAIL_CLASS_SYMBOL master_and_slaves
:
	public sge::rucksack::widget::base
{
	FCPPT_NONCOPYABLE(
		master_and_slaves
	);
public:
	SGE_RUCKSACK_DETAIL_SYMBOL
	explicit
	master_and_slaves(
		sge::rucksack::padding const &
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
	void
	master_pane(
		sge::rucksack::widget::base &
	);

	SGE_RUCKSACK_DETAIL_SYMBOL
	void
	push_back_child(
		sge::rucksack::widget::base &
	);

	SGE_RUCKSACK_DETAIL_SYMBOL
	~master_and_slaves()
	override;
private:
	sge::rucksack::widget::box surrounding_box_;

	sge::rucksack::widget::optional_ref master_pane_;

	sge::rucksack::widget::enumeration enumeration_;

	sge::rucksack::vector position_;

	sge::rucksack::dim size_;
};

}
}
}

#endif
