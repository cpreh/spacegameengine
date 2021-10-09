//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_WLINPUT_FOCUS_XKB_KEYSYM_HPP_INCLUDED
#define SGE_WLINPUT_FOCUS_XKB_KEYSYM_HPP_INCLUDED

#include <fcppt/declare_strong_typedef.hpp>
#include <fcppt/strong_typedef.hpp>
#include <fcppt/config/external_begin.hpp>
#include <xkbcommon/xkbcommon.h>
#include <fcppt/config/external_end.hpp>

namespace sge::wlinput::focus
{

FCPPT_DECLARE_STRONG_TYPEDEF(xkb_keysym_t, xkb_keysym);

}

#endif
