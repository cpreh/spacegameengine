//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_GUI_MASTER_HPP_INCLUDED
#define SGE_GUI_MASTER_HPP_INCLUDED

#include <sge/gui/context_ref.hpp>
#include <sge/gui/duration.hpp>
#include <sge/gui/master_fwd.hpp>
#include <sge/gui/background/base_fwd.hpp>
#include <sge/gui/detail/symbol.hpp>
#include <sge/gui/main_area/reference.hpp>
#include <sge/gui/renderer/base_fwd.hpp>
#include <sge/gui/widget/base_fwd.hpp>
#include <sge/gui/widget/optional_focus_fwd.hpp>
#include <sge/gui/widget/optional_ref_fwd.hpp>
#include <sge/input/event_base_fwd.hpp>
#include <sge/input/cursor/event/button_fwd.hpp>
#include <sge/input/focus/event/key_fwd.hpp>
#include <sge/input/focus/event/key_repeat_fwd.hpp>
#include <sge/input/focus/event/text_fwd.hpp>
#include <sge/input/key/code_fwd.hpp>
#include <sge/renderer/context/ffp_fwd.hpp>
#include <sge/renderer/device/ffp_fwd.hpp>
#include <fcppt/nonmovable.hpp>


namespace sge
{
namespace gui
{

class master
{
	FCPPT_NONMOVABLE(
		master
	);
public:
	SGE_GUI_DETAIL_SYMBOL
	master(
		sge::gui::context_ref,
		sge::gui::main_area::reference
	);

	SGE_GUI_DETAIL_SYMBOL
	~master(); // NOLINT(performance-trivially-destructible)

	SGE_GUI_DETAIL_SYMBOL
	void
	draw(
		sge::gui::renderer::base &, // NOLINT(google-runtime-references)
		sge::renderer::context::ffp &, // NOLINT(google-runtime-references)
		sge::gui::background::base & // NOLINT(google-runtime-references)
	); // NOLINT(google-runtime-references)

	SGE_GUI_DETAIL_SYMBOL
	void
	draw_with_states(
		sge::renderer::device::ffp &, // NOLINT(google-runtime-references)
		sge::renderer::context::ffp &, // NOLINT(google-runtime-references)
		sge::gui::background::base & // NOLINT(google-runtime-references)
	); // NOLINT(google-runtime-references)

	SGE_GUI_DETAIL_SYMBOL
	void
	update(
		sge::gui::duration
	);

	SGE_GUI_DETAIL_SYMBOL
	void
	process_event(
		sge::input::event_base const &
	);
private:
	void
	key_event(
		sge::input::focus::event::key const &
	);

	void
	key_repeat_event(
		sge::input::focus::event::key_repeat const &
	);

	void
	text_event(
		sge::input::focus::event::text const &
	);

	void
	button_event(
		sge::input::cursor::event::button const &
	);

	void
	handle_key(
		sge::input::key::code
	);

	[[nodiscard]]
	sge::gui::widget::optional_ref
	try_focus(
		sge::gui::widget::optional_focus
	);

	[[nodiscard]]
	sge::gui::widget::base &
	widget();

	sge::gui::context_ref const context_;

	sge::gui::main_area::reference const main_area_;
};

}
}

#endif
