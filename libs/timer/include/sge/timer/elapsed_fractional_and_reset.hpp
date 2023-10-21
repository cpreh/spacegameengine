//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_TIMER_ELAPSED_FRACTIONAL_AND_RESET_HPP_INCLUDED
#define SGE_TIMER_ELAPSED_FRACTIONAL_AND_RESET_HPP_INCLUDED

#include <sge/timer/basic.hpp>
#include <sge/timer/elapsed_fractional.hpp>
#include <fcppt/config/external_begin.hpp>
#include <type_traits>
#include <fcppt/config/external_end.hpp>

namespace sge::timer
{

template <typename Float, typename Clock>
Float elapsed_fractional_and_reset(sge::timer::basic<Clock> &_timer)
{
  static_assert(std::is_floating_point_v<Float>, "Float must be a floating point type");

  Float const ret{sge::timer::elapsed_fractional<Float>(_timer)};

  _timer.reset();

  return ret;
}

}

#endif
