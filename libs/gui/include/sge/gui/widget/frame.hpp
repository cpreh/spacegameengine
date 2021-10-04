//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_GUI_WIDGET_FRAME_HPP_INCLUDED
#define SGE_GUI_WIDGET_FRAME_HPP_INCLUDED

#include <sge/font/char_type.hpp>
#include <sge/gui/focus_change_fwd.hpp>
#include <sge/gui/get_focus_fwd.hpp>
#include <sge/gui/detail/symbol.hpp>
#include <sge/gui/renderer/base_fwd.hpp>
#include <sge/gui/style/const_reference.hpp>
#include <sge/gui/widget/base.hpp>
#include <sge/gui/widget/frame_fwd.hpp>
#include <sge/gui/widget/optional_focus_ref.hpp>
#include <sge/gui/widget/optional_ref_fwd.hpp>
#include <sge/gui/widget/reference.hpp>
#include <sge/input/key/code_fwd.hpp>
#include <sge/renderer/context/ffp_fwd.hpp>
#include <sge/rucksack/vector_fwd.hpp>
#include <sge/rucksack/widget/base_fwd.hpp>
#include <sge/rucksack/widget/frame.hpp>
#include <fcppt/nonmovable.hpp>


namespace sge::gui::widget
{

class frame
:
	public sge::gui::widget::base
{
	FCPPT_NONMOVABLE(
		frame
	);
public:
	SGE_GUI_DETAIL_SYMBOL
	frame(
		sge::gui::style::const_reference,
		sge::gui::widget::reference
	);

	SGE_GUI_DETAIL_SYMBOL
	~frame()
	override;

	[[nodiscard]]
	SGE_GUI_DETAIL_SYMBOL
	sge::rucksack::widget::base &
	layout()
	override;
private:
	void
	on_draw(
		sge::gui::renderer::base &,
		sge::renderer::context::ffp &
	)
	override;

	[[nodiscard]]
	sge::gui::get_focus
	on_click(
		sge::rucksack::vector const &
	)
	override;

	void
	on_key(
		sge::input::key::code
	)
	override;

	void
	on_char(
		sge::font::char_type
	)
	override;

	void
	on_focus_changed(
		sge::gui::focus_change
	)
	override;

	[[nodiscard]]
	sge::gui::widget::optional_ref
	on_tab(
		sge::gui::widget::optional_focus_ref
	)
	override;

	sge::gui::style::const_reference const style_;

	sge::gui::widget::reference const child_;

	sge::rucksack::widget::frame layout_;
};

}

#endif
