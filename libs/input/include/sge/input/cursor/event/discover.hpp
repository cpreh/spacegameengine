//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_INPUT_CURSOR_EVENT_DISCOVER_HPP_INCLUDED
#define SGE_INPUT_CURSOR_EVENT_DISCOVER_HPP_INCLUDED

#include <sge/core/detail/class_symbol.hpp>
#include <sge/input/cursor/shared_ptr.hpp>
#include <sge/input/cursor/event/base.hpp>
#include <sge/input/cursor/event/discover_fwd.hpp>
#include <fcppt/nonmovable.hpp>


namespace sge
{
namespace input
{
namespace cursor
{
namespace event
{

class SGE_CORE_DETAIL_CLASS_SYMBOL discover
:
	public sge::input::cursor::event::base
{
	FCPPT_NONMOVABLE(
		discover
	);
public:
	SGE_INPUT_DETAIL_SYMBOL
	explicit
	discover(
		sge::input::cursor::shared_ptr
	);

	SGE_INPUT_DETAIL_SYMBOL
	~discover()
	override;
};

}
}
}
}

#endif
