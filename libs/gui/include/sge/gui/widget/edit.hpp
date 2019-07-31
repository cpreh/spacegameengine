//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_GUI_WIDGET_EDIT_HPP_INCLUDED
#define SGE_GUI_WIDGET_EDIT_HPP_INCLUDED

#include <sge/font/char_type.hpp>
#include <sge/font/object_fwd.hpp>
#include <sge/font/string.hpp>
#include <sge/font/draw/static_text.hpp>
#include <sge/gui/duration.hpp>
#include <sge/gui/focus_change_fwd.hpp>
#include <sge/gui/get_focus_fwd.hpp>
#include <sge/gui/text_callback.hpp>
#include <sge/gui/text_function.hpp>
#include <sge/gui/detail/symbol.hpp>
#include <sge/gui/renderer/base_fwd.hpp>
#include <sge/gui/style/base_fwd.hpp>
#include <sge/gui/widget/base.hpp>
#include <sge/gui/widget/edit_fwd.hpp>
#include <sge/gui/widget/optional_focus_fwd.hpp>
#include <sge/gui/widget/optional_ref_fwd.hpp>
#include <sge/input/key/code_fwd.hpp>
#include <sge/renderer/context/ffp_fwd.hpp>
#include <sge/renderer/device/ffp_fwd.hpp>
#include <sge/rucksack/widget/base_fwd.hpp>
#include <sge/rucksack/widget/dummy.hpp>
#include <sge/timer/basic_decl.hpp>
#include <sge/timer/clocks/delta_decl.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/signal/auto_connection_fwd.hpp>
#include <fcppt/signal/object_decl.hpp>


namespace sge
{
namespace gui
{
namespace widget
{

class edit
:
	public sge::gui::widget::base
{
	FCPPT_NONCOPYABLE(
		edit
	);
public:
	SGE_GUI_DETAIL_SYMBOL
	edit(
		sge::gui::style::base const &,
		sge::renderer::device::ffp &,
		sge::font::object &,
		sge::font::string const &
	);

	SGE_GUI_DETAIL_SYMBOL
	~edit()
	override;

	SGE_GUI_DETAIL_SYMBOL
	sge::font::string const &
	text() const;

	SGE_GUI_DETAIL_SYMBOL
	fcppt::signal::auto_connection
	text_change(
		sge::gui::text_callback const &
	);

	SGE_GUI_DETAIL_SYMBOL
	sge::rucksack::widget::base &
	layout()
	override;
private:
	void
	on_update(
		sge::gui::duration
	)
	override;

	void
	on_draw(
		sge::gui::renderer::base &,
		sge::renderer::context::ffp &
	)
	override;

	sge::gui::get_focus
	on_click(
		sge::rucksack::vector
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

	sge::gui::widget::optional_ref
	on_tab(
		sge::gui::widget::optional_focus &
	)
	override;

	void
	text_changed();

	sge::font::draw::static_text
	make_static_text();

	sge::gui::style::base const &style_;

	sge::renderer::device::ffp &renderer_;

	sge::font::object &font_;

	sge::font::string text_;

	sge::font::string::size_type position_;

	sge::rucksack::widget::dummy layout_;

	sge::font::draw::static_text static_text_;

	typedef
	sge::timer::clocks::delta<
		sge::gui::duration
	>
	diff_clock;

	typedef
	sge::timer::basic<
		diff_clock
	>
	diff_timer;

	diff_clock clock_;

	diff_timer cursor_blink_timer_;

	bool has_focus_;

	bool show_cursor_;

	typedef
	fcppt::signal::object<
		sge::gui::text_function
	>
	text_signal;

	text_signal text_change_;
};

}
}
}

#endif
