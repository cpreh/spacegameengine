//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_EVDEV_INOTIFY_EVENT_TYPE_HPP_INCLUDED
#define SGE_EVDEV_INOTIFY_EVENT_TYPE_HPP_INCLUDED

#include <sge/evdev/inotify/event_type_fwd.hpp> // IWYU pragma: keep

namespace sge::evdev::inotify
{

enum class event_type
{
  add,
  remove,
  attrib
};

}

#endif
