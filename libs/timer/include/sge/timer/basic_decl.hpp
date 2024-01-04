//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_TIMER_BASIC_DECL_HPP_INCLUDED
#define SGE_TIMER_BASIC_DECL_HPP_INCLUDED

#include <sge/timer/basic_fwd.hpp> // IWYU pragma: keep
#include <sge/timer/parameters_decl.hpp>
#include <sge/timer/clocks/detail/wrapper.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/preprocessor/disable_gcc_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>

namespace sge::timer
{

FCPPT_PP_PUSH_WARNING
FCPPT_PP_DISABLE_GCC_WARNING(-Weffc++)

template <typename Clock>
class basic final : sge::timer::clocks::detail::wrapper<Clock>
{
  FCPPT_NONCOPYABLE(basic);

  using base = sge::timer::clocks::detail::wrapper<Clock>;

public:
  using clock_type = Clock;

  using parameters = sge::timer::parameters<clock_type>;

  using time_point = typename clock_type::time_point;

  using duration = typename clock_type::duration;

  explicit basic(parameters const &);

  basic(basic &&) noexcept;

  basic &operator=(basic &&) noexcept;

  ~basic();

  [[nodiscard]] bool expired() const;

  void expired(bool);

  [[nodiscard]] bool active() const;

  void active(bool);

  [[nodiscard]] duration interval() const;

  void interval(duration);

  [[nodiscard]] time_point now() const;

  [[nodiscard]] time_point last_time() const;

  void reset();

private:
  duration interval_;

  bool active_;

  bool expired_;

  time_point last_time_;
};

FCPPT_PP_POP_WARNING

}

#endif
