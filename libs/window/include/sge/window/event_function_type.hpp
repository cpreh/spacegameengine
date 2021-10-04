//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_WINDOW_EVENT_FUNCTION_TYPE_HPP_INCLUDED
#define SGE_WINDOW_EVENT_FUNCTION_TYPE_HPP_INCLUDED

#include <awl/event/container.hpp>
#include <awl/window/event/base_fwd.hpp>


namespace sge::window
{

using
event_function_type
=
awl::event::container (
	awl::window::event::base const &
);

}

#endif
