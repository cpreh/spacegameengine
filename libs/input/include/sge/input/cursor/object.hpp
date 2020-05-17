//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_INPUT_CURSOR_OBJECT_HPP_INCLUDED
#define SGE_INPUT_CURSOR_OBJECT_HPP_INCLUDED

#include <sge/core/detail/class_symbol.hpp>
#include <sge/input/cursor/mode_fwd.hpp>
#include <sge/input/cursor/object_fwd.hpp>
#include <sge/input/cursor/optional_position_fwd.hpp>
#include <sge/input/detail/symbol.hpp>
#include <sge/window/object_fwd.hpp>
#include <fcppt/nonmovable.hpp>


namespace sge
{
namespace input
{
namespace cursor
{

class SGE_CORE_DETAIL_CLASS_SYMBOL object
{
	FCPPT_NONMOVABLE(
		object
	);
protected:
	SGE_INPUT_DETAIL_SYMBOL
	object();
public:
	SGE_INPUT_DETAIL_SYMBOL
	virtual
	~object();

	[[nodiscard]]
	virtual
	sge::window::object &
	window() const = 0;

	[[nodiscard]]
	virtual
	sge::input::cursor::optional_position
	position() const = 0;

	virtual
	void
	mode(
		sge::input::cursor::mode
	) = 0;
};

}
}
}

#endif
