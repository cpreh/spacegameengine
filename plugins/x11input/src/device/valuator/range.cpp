//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/x11input/device/valuator/index.hpp>
#include <sge/x11input/device/valuator/iterator.hpp>
#include <sge/x11input/device/valuator/length.hpp>
#include <sge/x11input/device/valuator/range.hpp>
#include <fcppt/reference_impl.hpp>
#include <fcppt/config/external_begin.hpp>
#include <X11/extensions/XInput2.h>
#include <fcppt/config/external_end.hpp>

sge::x11input::device::valuator::range::range(fcppt::reference<XIValuatorState const> const _state)
    : state_{_state}
{
}

sge::x11input::device::valuator::range::iterator
sge::x11input::device::valuator::range::begin() const
{
  return sge::x11input::device::valuator::range::iterator{
      sge::x11input::device::valuator::index{0}, state_.get()};
}

sge::x11input::device::valuator::range::iterator sge::x11input::device::valuator::range::end() const
{
  return sge::x11input::device::valuator::range::iterator{
      sge::x11input::device::valuator::length(state_.get()), state_.get()};
}
