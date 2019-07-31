//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_WLINPUT_FOCUS_XKB_KEYCODE_HPP_INCLUDED
#define SGE_WLINPUT_FOCUS_XKB_KEYCODE_HPP_INCLUDED

#include <fcppt/make_strong_typedef.hpp>
#include <fcppt/strong_typedef.hpp>
#include <fcppt/config/external_begin.hpp>
#include <xkbcommon/xkbcommon.h>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace wlinput
{
namespace focus
{

FCPPT_MAKE_STRONG_TYPEDEF(
	xkb_keycode_t,
	xkb_keycode
);

}
}
}

#endif
