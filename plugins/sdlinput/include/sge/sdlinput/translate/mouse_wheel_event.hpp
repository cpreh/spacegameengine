//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_SDLINPUT_TRANSLATE_MOUSE_WHEEL_EVENT_HPP_INCLUDED
#define SGE_SDLINPUT_TRANSLATE_MOUSE_WHEEL_EVENT_HPP_INCLUDED

#include <sge/input/cursor/shared_ptr.hpp>
#include <sge/input/mouse/shared_ptr.hpp>
#include <awl/backends/sdl/window/object_fwd.hpp>
#include <awl/event/container.hpp>
#include <fcppt/config/external_begin.hpp>
#include <SDL_events.h>
#include <fcppt/config/external_end.hpp>

namespace sge::sdlinput::translate
{

awl::event::container mouse_wheel_event(
    sge::input::cursor::shared_ptr const &,
    sge::input::mouse::shared_ptr const &,
    awl::backends::sdl::window::object const &,
    SDL_MouseWheelEvent const &);

}

#endif
