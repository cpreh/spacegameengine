#include <sge/cegui/default_keyboard.hpp>
#include <sge/cegui/syringe.hpp>
#include <sge/input/keyboard/device.hpp>
#include <boost/bind.hpp>

sge::cegui::default_keyboard::default_keyboard(
	syringe &_syringe,
	sge::input::keyboard::device &_keyboard)
:
	syringe_(
		_syringe),
	key_callback_(
		_keyboard.key_callback(
			boost::bind(
				&default_keyboard::key_callback,
				this,
				_1))),
	key_repeat_callback_(
		_keyboard.key_repeat_callback(
			boost::bind(
				&default_keyboard::key_repeat_callback,
				this,
				_1))),
	char_callback_(
		_keyboard.char_callback(
			boost::bind(
				&default_keyboard::char_callback,
				this,
				_1)))
{
}

void
sge::cegui::default_keyboard::key_callback(
	sge::input::keyboard::key_event const &e)
{
	syringe_.inject(
		e);
}

void
sge::cegui::default_keyboard::key_repeat_callback(
	sge::input::keyboard::key_repeat_event const &e)
{
	syringe_.inject(
		e);
}

void
sge::cegui::default_keyboard::char_callback(
	sge::input::keyboard::char_event const &e)
{
	syringe_.inject(
		e);
}
