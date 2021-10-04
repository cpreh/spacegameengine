//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_INPUT_CURSOR_EVENT_SCROLL_HPP_INCLUDED
#define SGE_INPUT_CURSOR_EVENT_SCROLL_HPP_INCLUDED

#include <sge/core/detail/class_symbol.hpp>
#include <sge/input/cursor/scroll_code.hpp>
#include <sge/input/cursor/scroll_value.hpp>
#include <sge/input/cursor/shared_ptr.hpp>
#include <sge/input/cursor/event/base.hpp>
#include <sge/input/cursor/event/scroll_fwd.hpp>
#include <sge/input/detail/symbol.hpp>
#include <fcppt/nonmovable.hpp>


namespace sge::input::cursor::event
{

class SGE_CORE_DETAIL_CLASS_SYMBOL scroll
:
	public sge::input::cursor::event::base
{
	FCPPT_NONMOVABLE(
		scroll
	);
public:
	SGE_INPUT_DETAIL_SYMBOL
	scroll(
		sge::input::cursor::shared_ptr,
		sge::input::cursor::scroll_code,
		sge::input::cursor::scroll_value
	);

	SGE_INPUT_DETAIL_SYMBOL
	~scroll()
	override;

	[[nodiscard]]
	SGE_INPUT_DETAIL_SYMBOL
	sge::input::cursor::scroll_code
	code() const;

	[[nodiscard]]
	SGE_INPUT_DETAIL_SYMBOL
	sge::input::cursor::scroll_value
	value() const;
private:
	sge::input::cursor::scroll_code const code_;

	sge::input::cursor::scroll_value const value_;
};

}

#endif
