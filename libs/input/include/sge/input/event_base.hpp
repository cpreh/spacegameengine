//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_INPUT_EVENT_BASE_HPP_INCLUDED
#define SGE_INPUT_EVENT_BASE_HPP_INCLUDED

#include <sge/core/detail/class_symbol.hpp>
#include <sge/input/event_base_fwd.hpp>
#include <sge/input/detail/symbol.hpp>
#include <sge/window/object_fwd.hpp>
#include <awl/window/event/base.hpp>
#include <fcppt/nonmovable.hpp>


namespace sge::input
{

class SGE_CORE_DETAIL_CLASS_SYMBOL event_base
:
	public awl::window::event::base
{
	FCPPT_NONMOVABLE(
		event_base
	);
public:
	SGE_INPUT_DETAIL_SYMBOL
	explicit
	event_base(
		sge::window::object const &
	);

	SGE_INPUT_DETAIL_SYMBOL
	~event_base()
	override;
};

}

#endif
