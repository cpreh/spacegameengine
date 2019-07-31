//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_DINPUT_KEYBOARD_KEY_MAP_HPP_INCLUDED
#define SGE_DINPUT_KEYBOARD_KEY_MAP_HPP_INCLUDED

#include <sge/dinput/di.hpp>
#include <sge/input/key/code.hpp>
#include <fcppt/config/external_begin.hpp>
#include <unordered_map>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace dinput
{
namespace keyboard
{

typedef
std::unordered_map<
	DWORD,
	sge::input::key::code
>
key_map;

}
}
}

#endif
