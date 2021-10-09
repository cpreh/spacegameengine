//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_X11INPUT_DEVICE_VALUATOR_ACCU_MAP_HPP_INCLUDED
#define SGE_X11INPUT_DEVICE_VALUATOR_ACCU_MAP_HPP_INCLUDED

#include <sge/x11input/device/valuator/accu.hpp>
#include <sge/x11input/device/valuator/index.hpp>
#include <fcppt/config/external_begin.hpp>
#include <unordered_map>
#include <fcppt/config/external_end.hpp>

namespace sge::x11input::device::valuator
{

using accu_map = std::
    unordered_map<sge::x11input::device::valuator::index, sge::x11input::device::valuator::accu>;

}

#endif
