#ifndef SGE_GUI_MASTER_HPP_INCLUDED
#define SGE_GUI_MASTER_HPP_INCLUDED

#include <sge/gui/context_fwd.hpp>
#include <sge/gui/duration.hpp>
#include <sge/gui/master_fwd.hpp>
#include <sge/gui/detail/symbol.hpp>
#include <sge/gui/background/base_fwd.hpp>
#include <sge/gui/main_area/base_fwd.hpp>
#include <sge/gui/renderer/base_fwd.hpp>
#include <sge/gui/widget/base_fwd.hpp>
#include <sge/gui/widget/optional_focus_fwd.hpp>
#include <sge/gui/widget/optional_ref_fwd.hpp>
#include <sge/input/cursor/button_event_fwd.hpp>
#include <sge/input/cursor/object_fwd.hpp>
#include <sge/input/keyboard/char_event_fwd.hpp>
#include <sge/input/keyboard/device_fwd.hpp>
#include <sge/input/keyboard/key_code_fwd.hpp>
#include <sge/input/keyboard/key_event_fwd.hpp>
#include <sge/input/keyboard/key_repeat_event_fwd.hpp>
#include <sge/renderer/context/ffp_fwd.hpp>
#include <sge/renderer/device/ffp_fwd.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/signal/scoped_connection.hpp>


namespace sge
{
namespace gui
{

class master
{
	FCPPT_NONCOPYABLE(
		master
	);
public:
	SGE_GUI_DETAIL_SYMBOL
	master(
		sge::input::keyboard::device &,
		sge::input::cursor::object &,
		sge::gui::context &,
		sge::gui::main_area::base &
	);

	SGE_GUI_DETAIL_SYMBOL
	~master();

	SGE_GUI_DETAIL_SYMBOL
	void
	draw(
		sge::gui::renderer::base &,
		sge::renderer::context::ffp &,
		sge::gui::background::base &
	);

	SGE_GUI_DETAIL_SYMBOL
	void
	draw_with_states(
		sge::renderer::device::ffp &,
		sge::renderer::context::ffp &,
		sge::gui::background::base &
	);

	SGE_GUI_DETAIL_SYMBOL
	void
	update(
		sge::gui::duration
	);
private:
	void
	key_event(
		sge::input::keyboard::key_event const &
	);

	void
	key_repeat_event(
		sge::input::keyboard::key_repeat_event const &
	);

	void
	char_event(
		sge::input::keyboard::char_event const &
	);

	void
	button_event(
		sge::input::cursor::button_event const &
	);

	void
	handle_key(
		sge::input::keyboard::key_code
	);

	sge::gui::widget::optional_ref const
	try_focus(
		sge::gui::widget::optional_focus
	);

	sge::gui::widget::base &
	widget();

	sge::input::cursor::object &cursor_;

	sge::gui::context &context_;

	sge::gui::main_area::base &main_area_;

	fcppt::signal::scoped_connection const
		key_connection_,
		key_repeat_connection_,
		char_connection_,
		button_connection_;
};

}
}

#endif
