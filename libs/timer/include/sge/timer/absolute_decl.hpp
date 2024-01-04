//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_TIMER_ABSOLUTE_DECL_HPP_INCLUDED
#define SGE_TIMER_ABSOLUTE_DECL_HPP_INCLUDED

#include <sge/timer/absolute_fwd.hpp> // IWYU pragma: keep
#include <sge/timer/clocks/parameter.hpp>
#include <sge/timer/clocks/detail/wrapper.hpp>
#include <fcppt/nonmovable.hpp>

namespace sge::timer
{

template <typename Clock>
class absolute final : sge::timer::clocks::detail::wrapper<Clock>
{
  FCPPT_NONMOVABLE(absolute);

  using base = sge::timer::clocks::detail::wrapper<Clock>;

public:
  using clock_type = Clock;

  using time_point = typename clock_type::time_point;

  using duration = typename clock_type::duration;

  using clock_parameter = sge::timer::clocks::parameter<Clock>;

  absolute();

  explicit absolute(clock_parameter);

  ~absolute();

  [[nodiscard]] time_point now() const;

  [[nodiscard]] time_point last_time() const;

  void reset();

private:
  time_point last_time_;
};

}

#endif
