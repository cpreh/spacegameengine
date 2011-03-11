#ifndef SGE_CEGUI_DEFAULT_KEYBOARD_HPP_INCLUDED
#define SGE_CEGUI_DEFAULT_KEYBOARD_HPP_INCLUDED

#include <sge/cegui/syringe_fwd.hpp>
#include <sge/cegui/symbol.hpp>
#include <sge/input/keyboard/device_fwd.hpp>
#include <sge/input/keyboard/key_event_fwd.hpp>
#include <sge/input/keyboard/key_repeat_event_fwd.hpp>
#include <sge/input/keyboard/char_event_fwd.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/signal/scoped_connection.hpp>

namespace sge
{
namespace cegui
{
class default_keyboard
{
FCPPT_NONCOPYABLE(
	default_keyboard);
public:
	SGE_CEGUI_SYMBOL explicit
	default_keyboard(
		syringe &,
		sge::input::keyboard::device &);
private:
	syringe &syringe_;
	fcppt::signal::scoped_connection 
		key_callback_,
		key_repeat_callback_,
		char_callback_;

	void
	key_callback(
		sge::input::keyboard::key_event const &);

	void
	key_repeat_callback(
		sge::input::keyboard::key_repeat_event const &);

	void
	char_callback(
		sge::input::keyboard::char_event const &);
};
}
}

#endif
