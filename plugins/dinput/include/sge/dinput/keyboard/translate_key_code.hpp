//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_DINPUT_KEYBOARD_TRANSLATE_KEY_CODE_HPP_INCLUDED
#define SGE_DINPUT_KEYBOARD_TRANSLATE_KEY_CODE_HPP_INCLUDED

#include <sge/dinput/di.hpp>
#include <sge/input/key/code_fwd.hpp>

namespace sge
{
namespace dinput
{
namespace keyboard
{

sge::input::key::code translate_key_code(DWORD ofs);

}
}
}

#endif
