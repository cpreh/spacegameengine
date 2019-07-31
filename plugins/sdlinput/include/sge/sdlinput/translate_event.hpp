//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_SDLINPUT_TRANSLATE_EVENT_HPP_INCLUDED
#define SGE_SDLINPUT_TRANSLATE_EVENT_HPP_INCLUDED

#include <sge/input/cursor/shared_ptr.hpp>
#include <sge/input/focus/shared_ptr.hpp>
#include <sge/input/keyboard/shared_ptr.hpp>
#include <sge/input/mouse/shared_ptr.hpp>
#include <awl/backends/sdl/system/event/object_fwd.hpp>
#include <awl/backends/sdl/window/object_fwd.hpp>
#include <awl/event/container.hpp>


namespace sge
{
namespace sdlinput
{

awl::event::container
translate_event(
	sge::input::cursor::shared_ptr const &,
	sge::input::focus::shared_ptr const &,
	sge::input::keyboard::shared_ptr const &,
	sge::input::mouse::shared_ptr const &,
	awl::backends::sdl::window::object const &,
	awl::backends::sdl::system::event::object const &
);

}
}

#endif
