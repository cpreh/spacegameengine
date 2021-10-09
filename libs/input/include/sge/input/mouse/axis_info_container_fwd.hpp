//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_INPUT_MOUSE_AXIS_INFO_CONTAINER_FWD_HPP_INCLUDED
#define SGE_INPUT_MOUSE_AXIS_INFO_CONTAINER_FWD_HPP_INCLUDED

#include <sge/input/info/container_fwd.hpp>
#include <sge/input/mouse/axis_id.hpp>
#include <sge/input/mouse/axis_info_fwd.hpp>

namespace sge::input::mouse
{

using axis_info_container =
    sge::input::info::container<sge::input::mouse::axis_id, sge::input::mouse::axis_info>;

}

#endif
