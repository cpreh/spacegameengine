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


#ifndef SGE_GUI_WIDGET_BAR_HPP_INCLUDED
#define SGE_GUI_WIDGET_BAR_HPP_INCLUDED

#include <sge/gui/fill_color.hpp>
#include <sge/gui/fill_level.hpp>
#include <sge/gui/detail/symbol.hpp>
#include <sge/gui/renderer/base_fwd.hpp>
#include <sge/gui/style/base_fwd.hpp>
#include <sge/gui/widget/bar_fwd.hpp>
#include <sge/gui/widget/base.hpp>
#include <sge/renderer/context/ffp_fwd.hpp>
#include <sge/rucksack/axis.hpp>
#include <sge/rucksack/dim_fwd.hpp>
#include <sge/rucksack/widget/base_fwd.hpp>
#include <sge/rucksack/widget/dummy.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/strong_typedef.hpp>


namespace sge
{
namespace gui
{
namespace widget
{

class bar
:
	public sge::gui::widget::base
{
	FCPPT_NONCOPYABLE(
		bar
	);
public:
	SGE_GUI_DETAIL_SYMBOL
	bar(
		sge::gui::style::base const &,
		sge::rucksack::dim,
		sge::rucksack::axis,
		sge::gui::fill_color const &,
		sge::gui::fill_level
	);

	SGE_GUI_DETAIL_SYMBOL
	~bar()
	override;

	SGE_GUI_DETAIL_SYMBOL
	void
	value(
		sge::gui::fill_level
	);
private:
	void
	on_draw(
		sge::gui::renderer::base &,
		sge::renderer::context::ffp &
	)
	override;

	sge::rucksack::widget::base &
	layout()
	override;

	sge::gui::style::base const &style_;

	sge::rucksack::axis const axis_;

	sge::gui::fill_color const foreground_;

	sge::gui::fill_level value_;

	sge::rucksack::widget::dummy layout_;
};

}
}
}

#endif
