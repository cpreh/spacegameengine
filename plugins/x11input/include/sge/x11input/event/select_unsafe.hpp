//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_X11INPUT_EVENT_SELECT_UNSAFE_HPP_INCLUDED
#define SGE_X11INPUT_EVENT_SELECT_UNSAFE_HPP_INCLUDED

#include <sge/x11input/device/id.hpp>
#include <sge/x11input/event/type_container.hpp>
#include <awl/backends/x11/window/base_fwd.hpp>

namespace sge::x11input::event
{

void select_unsafe(
    awl::backends::x11::window::base const &,
    sge::x11input::device::id,
    sge::x11input::event::type_container const &);

}

#endif
