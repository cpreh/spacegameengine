//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_WLINPUT_FOCUS_TRANSLATE_KEYSYM_HPP_INCLUDED
#define SGE_WLINPUT_FOCUS_TRANSLATE_KEYSYM_HPP_INCLUDED

#include <sge/input/key/code.hpp>
#include <sge/wlinput/focus/xkb_keysym.hpp>

namespace sge::wlinput::focus
{

sge::input::key::code translate_keysym(sge::wlinput::focus::xkb_keysym);

}

#endif
