//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_INPUT_JOYPAD_EVENT_BUTTON_HPP_INCLUDED
#define SGE_INPUT_JOYPAD_EVENT_BUTTON_HPP_INCLUDED

#include <sge/core/detail/class_symbol.hpp>
#include <sge/input/detail/symbol.hpp>
#include <sge/input/joypad/button_id.hpp>
#include <sge/input/joypad/button_pressed.hpp>
#include <sge/input/joypad/shared_ptr.hpp>
#include <sge/input/joypad/event/base.hpp>
#include <sge/input/joypad/event/button_fwd.hpp>
#include <fcppt/nonmovable.hpp>


namespace sge::input::joypad::event
{

class SGE_CORE_DETAIL_CLASS_SYMBOL button
:
	public sge::input::joypad::event::base
{
	FCPPT_NONMOVABLE(
		button
	);
public:
	SGE_INPUT_DETAIL_SYMBOL
	button(
		sge::input::joypad::shared_ptr,
		sge::input::joypad::button_id,
		sge::input::joypad::button_pressed
	);

	SGE_INPUT_DETAIL_SYMBOL
	~button()
	override;

	[[nodiscard]]
	SGE_INPUT_DETAIL_SYMBOL
	sge::input::joypad::button_id
	button_id() const;

	[[nodiscard]]
	SGE_INPUT_DETAIL_SYMBOL
	bool
	pressed() const;
private:
	sge::input::joypad::button_id const button_id_;

	sge::input::joypad::button_pressed const pressed_;
};

}

#endif
