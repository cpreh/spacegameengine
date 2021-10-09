//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/x11input/device/valuator/index.hpp>
#include <sge/x11input/device/valuator/length.hpp>
#include <fcppt/config/external_begin.hpp>
#include <X11/extensions/XInput2.h>
#include <climits>
#include <fcppt/config/external_end.hpp>

sge::x11input::device::valuator::index
sge::x11input::device::valuator::length(XIValuatorState const &_valuators)
{
  return sge::x11input::device::valuator::index{_valuators.mask_len * CHAR_BIT};
}
