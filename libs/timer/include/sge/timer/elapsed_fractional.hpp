//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_TIMER_ELAPSED_FRACTIONAL_HPP_INCLUDED
#define SGE_TIMER_ELAPSED_FRACTIONAL_HPP_INCLUDED

#include <sge/timer/basic.hpp>
#include <sge/timer/elapsed.hpp>
#include <fcppt/config/external_begin.hpp>
#include <chrono>
#include <type_traits>
#include <fcppt/config/external_end.hpp>

namespace sge::timer
{

template <typename Float, typename Clock>
Float elapsed_fractional(sge::timer::basic<Clock> const &_timer)
{
  static_assert(std::is_floating_point_v<Float>, "Float must be a floating point type");

  using float_duration = std::chrono::duration<Float, typename Clock::period>;

  return std::chrono::duration_cast<float_duration>(sge::timer::elapsed(_timer)) /
         std::chrono::duration_cast<float_duration>(_timer.interval());
}

}

#endif
