//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_SDLINPUT_JOYPAD_FROM_EVENT_HPP_INCLUDED
#define SGE_SDLINPUT_JOYPAD_FROM_EVENT_HPP_INCLUDED

#include <sge/sdlinput/joypad/from_event_impl.hpp>
#include <sge/sdlinput/joypad/map.hpp>
#include <sge/sdlinput/joypad/shared_ptr.hpp>


namespace sge
{
namespace sdlinput
{
namespace joypad
{

template<
	typename Event
>
sge::sdlinput::joypad::shared_ptr
from_event(
	sge::sdlinput::joypad::map const &_joypads,
	Event const &_event
)
{
	return
		sge::sdlinput::joypad::from_event_impl(
			_joypads,
			_event.which
		);
}

}
}
}

#endif
