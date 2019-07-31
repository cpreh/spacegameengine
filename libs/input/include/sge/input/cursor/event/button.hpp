//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_INPUT_CURSOR_EVENT_BUTTON_HPP_INCLUDED
#define SGE_INPUT_CURSOR_EVENT_BUTTON_HPP_INCLUDED

#include <sge/core/detail/class_symbol.hpp>
#include <sge/input/cursor/button_code.hpp>
#include <sge/input/cursor/button_pressed.hpp>
#include <sge/input/cursor/position.hpp>
#include <sge/input/cursor/shared_ptr.hpp>
#include <sge/input/cursor/event/base.hpp>
#include <sge/input/cursor/event/button_fwd.hpp>
#include <sge/input/detail/symbol.hpp>
#include <fcppt/noncopyable.hpp>


namespace sge
{
namespace input
{
namespace cursor
{
namespace event
{

class SGE_CORE_DETAIL_CLASS_SYMBOL button
:
	public sge::input::cursor::event::base
{
	FCPPT_NONCOPYABLE(
		button
	);
public:
	SGE_INPUT_DETAIL_SYMBOL
	button(
		sge::input::cursor::shared_ptr,
		sge::input::cursor::button_code,
		sge::input::cursor::position,
		sge::input::cursor::button_pressed
	);

	SGE_INPUT_DETAIL_SYMBOL
	~button()
	override;

	SGE_INPUT_DETAIL_SYMBOL
	sge::input::cursor::button_code
	button_code() const;

	SGE_INPUT_DETAIL_SYMBOL
	sge::input::cursor::position
	position() const;

	SGE_INPUT_DETAIL_SYMBOL
	bool
	pressed() const;
private:
	sge::input::cursor::button_code const button_code_;

	sge::input::cursor::position const position_;

	sge::input::cursor::button_pressed const pressed_;
};

}
}
}
}

#endif
