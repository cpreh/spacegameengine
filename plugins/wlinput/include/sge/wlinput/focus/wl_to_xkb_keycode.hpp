//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_WLINPUT_FOCUS_WL_TO_XKB_KEYCODE_HPP_INCLUDED
#define SGE_WLINPUT_FOCUS_WL_TO_XKB_KEYCODE_HPP_INCLUDED

#include <sge/wlinput/focus/xkb_keycode.hpp>
#include <fcppt/config/external_begin.hpp>
#include <cstdint>
#include <fcppt/config/external_end.hpp>

namespace sge::wlinput::focus
{

sge::wlinput::focus::xkb_keycode wl_to_xkb_keycode(std::uint32_t);

}

#endif
