//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_EVDEV_INOTIFY_EVENT_CONTAINER_HPP_INCLUDED
#define SGE_EVDEV_INOTIFY_EVENT_CONTAINER_HPP_INCLUDED

#include <sge/evdev/inotify/event.hpp>
#include <fcppt/config/external_begin.hpp>
#include <vector>
#include <fcppt/config/external_end.hpp>

namespace sge::evdev::inotify
{

using event_container = std::vector<sge::evdev::inotify::event>;

}

#endif
