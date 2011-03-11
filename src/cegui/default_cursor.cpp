#include <sge/cegui/default_cursor.hpp>
#include <sge/cegui/syringe.hpp>
#include <sge/input/cursor/object.hpp>
#include <boost/bind.hpp>

sge::cegui::default_cursor::default_cursor(
	syringe &_syringe,
	sge::input::cursor::object &_cursor)
:
	syringe_(
		_syringe),
	button_connection_(
		_cursor.button_callback(
			boost::bind(
				&default_cursor::button_callback,
				this,
				_1))),
	axis_connection_(
		_cursor.move_callback(
			boost::bind(
				&default_cursor::move_callback,
				this,
				_1)))
{
	syringe_.inject(
		_cursor.position());
}

void
sge::cegui::default_cursor::button_callback(
	sge::input::cursor::button_event const &e)
{
	syringe_.inject(
		e);
}

void
sge::cegui::default_cursor::move_callback(
	sge::input::cursor::move_event const &e)
{
	syringe_.inject(
		e);
}
