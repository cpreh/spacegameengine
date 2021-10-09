//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_SDLINPUT_SAME_WINDOWS_HPP_INCLUDED
#define SGE_SDLINPUT_SAME_WINDOWS_HPP_INCLUDED

#include <sge/sdlinput/same_windows_impl.hpp>
#include <awl/backends/sdl/window/object_fwd.hpp>

namespace sge::sdlinput
{

template <typename Event>
bool same_windows(awl::backends::sdl::window::object const &_window, Event const &_event)
{
  return sge::sdlinput::same_windows_impl(_window, _event.windowID);
}

}

#endif
