//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_OPENGL_EVENT_HANDLER_HPP_INCLUDED
#define SGE_OPENGL_EVENT_HANDLER_HPP_INCLUDED

#include <sge/window/system_event_function.hpp>
#include <awl/timer/const_reference.hpp>
#include <awl/window/object_ref.hpp>

namespace sge::opengl
{

[[nodiscard]] sge::window::system_event_function
    event_handler(awl::window::object_ref, awl::timer::const_reference);

}

#endif
