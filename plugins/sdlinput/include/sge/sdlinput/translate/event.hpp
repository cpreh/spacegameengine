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
#include <sge/sdlinput/joypad/map.hpp>
#include <sge/window/object_ref.hpp>
#include <awl/backends/sdl/system/event/object_fwd.hpp>
#include <awl/backends/sdl/window/object_fwd.hpp>
#include <awl/event/container.hpp>
#include <fcppt/reference_fwd.hpp>


namespace sge::sdlinput::translate
{

awl::event::container
event(
	fcppt::reference<
		sge::sdlinput::joypad::map
	>,
	sge::input::cursor::shared_ptr const &,
	sge::input::focus::shared_ptr const &,
	sge::input::keyboard::shared_ptr const &,
	sge::input::mouse::shared_ptr const &,
	sge::window::object_ref,
	awl::backends::sdl::window::object const &,
	awl::backends::sdl::system::event::object const &
);

}

#endif
