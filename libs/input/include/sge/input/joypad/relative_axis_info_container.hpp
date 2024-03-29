//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_INPUT_JOYPAD_RELATIVE_AXIS_INFO_CONTAINER_HPP_INCLUDED
#define SGE_INPUT_JOYPAD_RELATIVE_AXIS_INFO_CONTAINER_HPP_INCLUDED

#include <sge/input/info/detail/declare_container.hpp>
#include <sge/input/joypad/relative_axis_id.hpp>
#include <sge/input/joypad/relative_axis_info.hpp>
#include <sge/input/joypad/relative_axis_info_container_fwd.hpp> // IWYU pragma: export

SGE_INPUT_INFO_DETAIL_DECLARE_CONTAINER(
    sge::input::joypad::relative_axis_id, sge::input::joypad::relative_axis_info);

#endif
