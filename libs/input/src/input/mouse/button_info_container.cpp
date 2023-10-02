//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/input/impl/info/instantiate_container.hpp>
#include <sge/input/mouse/button_id.hpp>
#include <sge/input/mouse/button_info.hpp>
#include <sge/input/mouse/button_info_container.hpp> // NOLINT(misc-include-cleaner)

SGE_INPUT_IMPL_INFO_INSTANTIATE_CONTAINER(
    sge::input::mouse::button_id, sge::input::mouse::button_info);
