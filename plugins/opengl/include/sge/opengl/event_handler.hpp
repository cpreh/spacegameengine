//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_OPENGL_EVENT_HANDLER_HPP_INCLUDED
#define SGE_OPENGL_EVENT_HANDLER_HPP_INCLUDED

#include <sge/window/system_event_function.hpp>
#include <awl/timer/object_fwd.hpp>
#include <awl/window/object_fwd.hpp>


namespace sge
{
namespace opengl
{

sge::window::system_event_function
event_handler(
	awl::window::object &,
	awl::timer::object const &
);

}
}

#endif
