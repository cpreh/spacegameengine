//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_WINDOW_SYSTEM_EVENT_FUNCTION_TYPE_HPP_INCLUDED
#define SGE_WINDOW_SYSTEM_EVENT_FUNCTION_TYPE_HPP_INCLUDED

#include <awl/event/base_fwd.hpp>
#include <awl/event/container.hpp>

namespace sge::window
{

using system_event_function_type = awl::event::container(awl::event::base const &);

}

#endif
