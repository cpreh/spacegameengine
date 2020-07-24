//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_GUI_WIDGET_BAR_HPP_INCLUDED
#define SGE_GUI_WIDGET_BAR_HPP_INCLUDED

#include <sge/gui/fill_color.hpp>
#include <sge/gui/fill_level.hpp>
#include <sge/gui/detail/symbol.hpp>
#include <sge/gui/renderer/base_fwd.hpp>
#include <sge/gui/style/const_reference.hpp>
#include <sge/gui/widget/bar_fwd.hpp>
#include <sge/gui/widget/base.hpp>
#include <sge/renderer/context/ffp_fwd.hpp>
#include <sge/rucksack/axis.hpp>
#include <sge/rucksack/dim_fwd.hpp>
#include <sge/rucksack/widget/base_fwd.hpp>
#include <sge/rucksack/widget/dummy.hpp>
#include <fcppt/nonmovable.hpp>
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
	FCPPT_NONMOVABLE(
		bar
	);
public:
	SGE_GUI_DETAIL_SYMBOL
	bar(
		sge::gui::style::const_reference,
		sge::rucksack::dim const &,
		sge::rucksack::axis,
		sge::gui::fill_color,
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

	[[nodiscard]]
	sge::rucksack::widget::base &
	layout()
	override;

	sge::gui::style::const_reference const style_;

	sge::rucksack::axis const axis_;

	sge::gui::fill_color const foreground_;

	sge::gui::fill_level value_;

	sge::rucksack::widget::dummy layout_;
};

}
}
}

#endif
