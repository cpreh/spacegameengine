#ifndef SGE_CEGUI_DETAIL_INPUT_HPP_INCLUDED
#define SGE_CEGUI_DETAIL_INPUT_HPP_INCLUDED

#include <sge/input/keyboard/device_fwd.hpp>
#include <sge/input/keyboard/key_event_fwd.hpp>
#include <sge/input/keyboard/key_repeat_event_fwd.hpp>
#include <sge/input/keyboard/char_event_fwd.hpp>
#include <sge/input/mouse/device_fwd.hpp>
#include <sge/input/mouse/button_event_fwd.hpp>
#include <sge/input/mouse/axis_event_fwd.hpp>
#include <sge/charconv/system_ptr.hpp>
#include <sge/time/funit.hpp>
#include <fcppt/signal/scoped_connection.hpp>

namespace CEGUI
{
class System;
}

namespace sge
{
namespace cegui
{
namespace detail
{
class input
{
public:
	explicit
	input(
		sge::input::keyboard::device &,
		sge::input::mouse::device &,
		sge::charconv::system_ptr,
		CEGUI::System &);

	void
	update(
		sge::time::funit);
private:
	CEGUI::System &system_;
	sge::charconv::system_ptr charconv_system_;
	fcppt::signal::scoped_connection 
		key_callback_,
		key_repeat_callback_,
		char_callback_,
		mouse_button_callback_,
		mouse_axis_callback_;

	void
	key_callback(
		sge::input::keyboard::key_event const &);

	void
	key_repeat_callback(
		sge::input::keyboard::key_repeat_event const &);

	void
	char_callback(
		sge::input::keyboard::char_event const &);

	void
	mouse_button_callback(
		sge::input::mouse::button_event const &);

	void
	mouse_axis_callback(
		sge::input::mouse::axis_event const &);
};
}
}
}

#endif
