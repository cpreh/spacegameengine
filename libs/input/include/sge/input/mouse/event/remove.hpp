//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_INPUT_MOUSE_EVENT_REMOVE_HPP_INCLUDED
#define SGE_INPUT_MOUSE_EVENT_REMOVE_HPP_INCLUDED

#include <sge/core/detail/class_symbol.hpp>
#include <sge/input/detail/symbol.hpp>
#include <sge/input/mouse/shared_ptr.hpp>
#include <sge/input/mouse/event/base.hpp>
#include <sge/input/mouse/event/remove_fwd.hpp>
#include <fcppt/nonmovable.hpp>


namespace sge::input::mouse::event
{

class SGE_CORE_DETAIL_CLASS_SYMBOL remove
:
	public sge::input::mouse::event::base
{
	FCPPT_NONMOVABLE(
		remove
	);
public:
	SGE_INPUT_DETAIL_SYMBOL
	explicit
	remove(
		sge::input::mouse::shared_ptr
	);

	SGE_INPUT_DETAIL_SYMBOL
	~remove()
	override;
};

}

#endif
