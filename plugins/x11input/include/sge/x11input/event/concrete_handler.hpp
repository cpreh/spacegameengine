//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_X11INPUT_EVENT_CONCRETE_HANDLER_HPP_INCLUDED
#define SGE_X11INPUT_EVENT_CONCRETE_HANDLER_HPP_INCLUDED

#include <awl/event/container.hpp>
#include <fcppt/function_impl.hpp>

namespace sge::x11input::event
{

template <typename Event>
using concrete_handler = fcppt::function<awl::event::container(Event const &)>;

}

#endif
