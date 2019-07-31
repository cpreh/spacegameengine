//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_WLINPUT_FOCUS_GET_KEYSYM_HPP_INCLUDED
#define SGE_WLINPUT_FOCUS_GET_KEYSYM_HPP_INCLUDED

#include <sge/wlinput/focus/state_fwd.hpp>
#include <sge/wlinput/focus/xkb_keycode.hpp>
#include <sge/wlinput/focus/xkb_keysym.hpp>


namespace sge
{
namespace wlinput
{
namespace focus
{

sge::wlinput::focus::xkb_keysym
get_keysym(
	sge::wlinput::focus::state const &,
	sge::wlinput::focus::xkb_keycode
);

}
}
}

#endif
