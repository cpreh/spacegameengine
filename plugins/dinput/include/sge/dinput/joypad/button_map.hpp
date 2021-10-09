//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_DINPUT_JOYPAD_BUTTON_MAP_HPP_INCLUDED
#define SGE_DINPUT_JOYPAD_BUTTON_MAP_HPP_INCLUDED

#include <sge/dinput/di.hpp>
#include <sge/input/joypad/button_id.hpp>
#include <fcppt/config/external_begin.hpp>
#include <unordered_map>
#include <fcppt/config/external_end.hpp>

namespace sge
{
namespace dinput
{
namespace joypad
{

typedef std::unordered_map<DWORD, sge::input::joypad::button_id> button_map;

}
}
}

#endif
