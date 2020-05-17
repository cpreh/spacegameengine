//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_INPUT_MOUSE_EVENT_BUTTON_HPP_INCLUDED
#define SGE_INPUT_MOUSE_EVENT_BUTTON_HPP_INCLUDED

#include <sge/core/detail/class_symbol.hpp>
#include <sge/input/detail/symbol.hpp>
#include <sge/input/mouse/button.hpp>
#include <sge/input/mouse/button_code_fwd.hpp>
#include <sge/input/mouse/button_pressed.hpp>
#include <sge/input/mouse/shared_ptr.hpp>
#include <sge/input/mouse/event/base.hpp>
#include <sge/input/mouse/event/button_fwd.hpp>
#include <fcppt/nonmovable.hpp>


namespace sge
{
namespace input
{
namespace mouse
{
namespace event
{

class SGE_CORE_DETAIL_CLASS_SYMBOL button
:
	public sge::input::mouse::event::base
{
	FCPPT_NONMOVABLE(
		button
	);
public:
	SGE_INPUT_DETAIL_SYMBOL
	button(
		sge::input::mouse::shared_ptr,
		sge::input::mouse::button const &,
		sge::input::mouse::button_pressed
	);

	SGE_INPUT_DETAIL_SYMBOL
	~button()
	override;

	[[nodiscard]]
	SGE_INPUT_DETAIL_SYMBOL
	sge::input::mouse::button_code
	button_code() const;

	[[nodiscard]]
	SGE_INPUT_DETAIL_SYMBOL
	sge::input::mouse::button const &
	get() const;

	[[nodiscard]]
	SGE_INPUT_DETAIL_SYMBOL
	bool
	pressed() const;
private:
	sge::input::mouse::button const button_;

	sge::input::mouse::button_pressed const pressed_;
};

}
}
}
}

#endif
