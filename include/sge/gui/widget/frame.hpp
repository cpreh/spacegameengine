#ifndef SGE_GUI_WIDGET_FRAME_HPP_INCLUDED
#define SGE_GUI_WIDGET_FRAME_HPP_INCLUDED

#include <sge/gui/focus_change_fwd.hpp>
#include <sge/gui/get_focus_fwd.hpp>
#include <sge/gui/detail/symbol.hpp>
#include <sge/gui/renderer/base_fwd.hpp>
#include <sge/gui/style/base_fwd.hpp>
#include <sge/gui/widget/base.hpp>
#include <sge/gui/widget/frame_fwd.hpp>
#include <sge/gui/widget/optional_focus_fwd.hpp>
#include <sge/gui/widget/optional_ref_fwd.hpp>
#include <sge/font/char_type.hpp>
#include <sge/input/keyboard/key_code_fwd.hpp>
#include <sge/renderer/context/ffp_fwd.hpp>
#include <sge/rucksack/vector_fwd.hpp>
#include <sge/rucksack/widget/base_fwd.hpp>
#include <sge/rucksack/widget/frame.hpp>
#include <fcppt/noncopyable.hpp>


namespace sge
{
namespace gui
{
namespace widget
{

class frame
:
	public sge::gui::widget::base
{
	FCPPT_NONCOPYABLE(
		frame
	);
public:
	SGE_GUI_DETAIL_SYMBOL
	frame(
		sge::gui::style::base const &,
		sge::gui::widget::base &
	);

	SGE_GUI_DETAIL_SYMBOL
	~frame()
	override;

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

	sge::gui::get_focus const
	on_click(
		sge::rucksack::vector
	)
	override;

	void
	on_key(
		sge::input::keyboard::key_code
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

	sge::gui::widget::optional_ref const
	on_tab(
		sge::gui::widget::optional_focus &
	)
	override;

	sge::gui::style::base const &style_;

	sge::gui::widget::base &child_;

	sge::rucksack::widget::frame layout_;
};

}
}
}

#endif
