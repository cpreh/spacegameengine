//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_WLINPUT_CURSOR_POSITION_HPP_INCLUDED
#define SGE_WLINPUT_CURSOR_POSITION_HPP_INCLUDED

#include <sge/input/cursor/position.hpp>
#include <fcppt/config/external_begin.hpp>
#include <wayland-util.h>
#include <fcppt/config/external_end.hpp>

namespace sge::wlinput::cursor
{

sge::input::cursor::position position(wl_fixed_t, wl_fixed_t);

}

#endif
