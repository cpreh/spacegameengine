//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_X11INPUT_DEVICE_VALUATOR_PAIR_HPP_INCLUDED
#define SGE_X11INPUT_DEVICE_VALUATOR_PAIR_HPP_INCLUDED

#include <sge/x11input/device/valuator/index.hpp>
#include <sge/x11input/device/valuator/pair_fwd.hpp>
#include <sge/x11input/device/valuator/value.hpp>

namespace sge::x11input::device::valuator
{

class pair
{
public:
  pair(sge::x11input::device::valuator::index, sge::x11input::device::valuator::value);

  [[nodiscard]] sge::x11input::device::valuator::index index() const;

  [[nodiscard]] sge::x11input::device::valuator::value value() const;

private:
  sge::x11input::device::valuator::index index_;

  sge::x11input::device::valuator::value value_;
};

}

#endif
