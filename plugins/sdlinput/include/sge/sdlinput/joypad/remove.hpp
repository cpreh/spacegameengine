//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_SDLINPUT_JOYPAD_REMOVE_HPP_INCLUDED
#define SGE_SDLINPUT_JOYPAD_REMOVE_HPP_INCLUDED

#include <sge/sdlinput/joypad/map.hpp>
#include <awl/event/container.hpp>
#include <fcppt/reference_fwd.hpp>
#include <fcppt/config/external_begin.hpp>
#include <SDL_events.h>
#include <fcppt/config/external_end.hpp>


namespace sge::sdlinput::joypad
{

awl::event::container
remove(
	fcppt::reference<
		sge::sdlinput::joypad::map
	>,
	SDL_JoyDeviceEvent const &
);

}

#endif
