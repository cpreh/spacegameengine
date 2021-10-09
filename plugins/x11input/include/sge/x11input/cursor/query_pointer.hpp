//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_X11INPUT_CURSOR_QUERY_POINTER_HPP_INCLUDED
#define SGE_X11INPUT_CURSOR_QUERY_POINTER_HPP_INCLUDED

#include <sge/input/cursor/optional_position_fwd.hpp>
#include <sge/x11input/device/id.hpp>
#include <awl/backends/x11/window/base_fwd.hpp>

namespace sge::x11input::cursor
{

sge::input::cursor::optional_position
query_pointer(awl::backends::x11::window::base const &, sge::x11input::device::id const &);

}

#endif
