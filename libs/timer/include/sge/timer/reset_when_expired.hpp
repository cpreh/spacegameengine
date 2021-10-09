//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_TIMER_RESET_WHEN_EXPIRED_HPP_INCLUDED
#define SGE_TIMER_RESET_WHEN_EXPIRED_HPP_INCLUDED

#include <sge/timer/basic.hpp>
#include <fcppt/reference_impl.hpp>

namespace sge::timer
{

template <typename Clock>
[[nodiscard]] bool reset_when_expired(fcppt::reference<sge::timer::basic<Clock>> const _timer)
{
  if (!_timer.get().expired())
  {
    return false;
  }

  _timer.get().reset();

  return true;
}

}

#endif
