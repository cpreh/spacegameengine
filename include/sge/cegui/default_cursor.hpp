#ifndef SGE_CEGUI_DEFAULT_CURSOR_HPP_INCLUDED
#define SGE_CEGUI_DEFAULT_CURSOR_HPP_INCLUDED

#include <sge/cegui/syringe_fwd.hpp>
#include <sge/cegui/symbol.hpp>
#include <sge/input/cursor/object_fwd.hpp>
#include <sge/input/cursor/button_event_fwd.hpp>
#include <sge/input/cursor/move_event_fwd.hpp>
#include <fcppt/signal/scoped_connection.hpp>
#include <fcppt/noncopyable.hpp>

namespace sge
{
namespace cegui
{
class default_cursor
{
FCPPT_NONCOPYABLE(
	default_cursor);
public:
	SGE_CEGUI_SYMBOL explicit
	default_cursor(
		syringe &,
		sge::input::cursor::object &);
private:
	syringe &syringe_;
	fcppt::signal::scoped_connection 
		button_connection_,
		axis_connection_;

	void
	button_callback(
		sge::input::cursor::button_event const &);

	void
	move_callback(
		sge::input::cursor::move_event const &);
};
}
}

#endif
