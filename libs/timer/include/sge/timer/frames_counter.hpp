//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_TIMER_FRAMES_COUNTER_HPP_INCLUDED
#define SGE_TIMER_FRAMES_COUNTER_HPP_INCLUDED

#include <sge/timer/basic_decl.hpp>
#include <sge/timer/frames_counter_fwd.hpp>
#include <sge/timer/clocks/standard.hpp>
#include <sge/timer/detail/symbol.hpp>
#include <fcppt/nonmovable.hpp>
#include <fcppt/string.hpp>
#include <fcppt/config/external_begin.hpp>
#include <cstdint>
#include <fcppt/config/external_end.hpp>

namespace sge::timer
{

class frames_counter
{
  FCPPT_NONMOVABLE(frames_counter);

public:
  using clock = sge::timer::clocks::standard;

  using counter = std::uint64_t;

  SGE_TIMER_DETAIL_SYMBOL
  frames_counter();

  SGE_TIMER_DETAIL_SYMBOL
  void update();

  [[nodiscard]] SGE_TIMER_DETAIL_SYMBOL counter frames() const;

  [[nodiscard]] SGE_TIMER_DETAIL_SYMBOL fcppt::string frames_str() const;

  SGE_TIMER_DETAIL_SYMBOL
  ~frames_counter();

private:
  sge::timer::basic<clock> timer_;

  counter current_frames_; // NOLINT(cppcoreguidelines-use-default-member-init,modernize-use-default-member-init)

  counter display_frames_; // NOLINT(cppcoreguidelines-use-default-member-init,modernize-use-default-member-init)
};

}

#endif
