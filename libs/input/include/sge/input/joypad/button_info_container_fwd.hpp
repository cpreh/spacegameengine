//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_INPUT_JOYPAD_BUTTON_INFO_CONTAINER_FWD_HPP_INCLUDED
#define SGE_INPUT_JOYPAD_BUTTON_INFO_CONTAINER_FWD_HPP_INCLUDED

#include <sge/input/info/container_fwd.hpp>
#include <sge/input/joypad/button_id.hpp>
#include <sge/input/joypad/button_info_fwd.hpp>


namespace sge
{
namespace input
{
namespace joypad
{

using
button_info_container
=
sge::input::info::container<
	sge::input::joypad::button_id,
	sge::input::joypad::button_info
>;

}
}
}

#endif
