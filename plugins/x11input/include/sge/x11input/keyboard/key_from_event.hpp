//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_X11INPUT_KEYBOARD_KEY_FROM_EVENT_HPP_INCLUDED
#define SGE_X11INPUT_KEYBOARD_KEY_FROM_EVENT_HPP_INCLUDED

#include <sge/input/keyboard/key.hpp>
#include <awl/backends/x11/display_fwd.hpp>
#include <fcppt/config/external_begin.hpp>
#include <X11/extensions/XInput2.h>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace x11input
{
namespace keyboard
{

sge::input::keyboard::key
key_from_event(
	awl::backends::x11::display const &,
	XIDeviceEvent const &
);

}
}
}

#endif
