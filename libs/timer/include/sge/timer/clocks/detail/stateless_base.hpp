//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_TIMER_CLOCKS_DETAIL_STATELESS_BASE_HPP_INCLUDED
#define SGE_TIMER_CLOCKS_DETAIL_STATELESS_BASE_HPP_INCLUDED

namespace sge::timer::clocks::detail
{

template <typename Clock>
class stateless_base
{
public:
  explicit stateless_base(Clock const &) {}

  [[nodiscard]] Clock clock_base() const { return Clock(); }
};

}

#endif
