//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_INPUT_PROCESSOR_HPP_INCLUDED
#define SGE_INPUT_PROCESSOR_HPP_INCLUDED

#include <sge/core/detail/class_symbol.hpp>
#include <sge/input/processor_fwd.hpp>
#include <sge/input/cursor/container.hpp>
#include <sge/input/detail/symbol.hpp>
#include <sge/input/focus/container.hpp>
#include <sge/input/joypad/container.hpp>
#include <sge/input/keyboard/container.hpp>
#include <sge/input/mouse/container.hpp>
#include <sge/window/object_fwd.hpp>
#include <fcppt/nonmovable.hpp>


namespace sge
{
namespace input
{

class SGE_CORE_DETAIL_CLASS_SYMBOL processor
{
	FCPPT_NONMOVABLE(
		processor
	);
protected:
	SGE_INPUT_DETAIL_SYMBOL
	processor();
public:
	SGE_INPUT_DETAIL_SYMBOL
	virtual
	~processor();

	[[nodiscard]]
	virtual
	sge::window::object &
	window() const = 0;

	[[nodiscard]]
	virtual
	sge::input::cursor::container
	cursors() const = 0;

	[[nodiscard]]
	virtual
	sge::input::focus::container
	foci() const = 0;

	[[nodiscard]]
	virtual
	sge::input::joypad::container
	joypads() const = 0;

	[[nodiscard]]
	virtual
	sge::input::keyboard::container
	keyboards() const = 0;

	[[nodiscard]]
	virtual
	sge::input::mouse::container
	mice() const = 0;
};

}
}

#endif
