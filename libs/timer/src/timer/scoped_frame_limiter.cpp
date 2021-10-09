//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/timer/scoped_frame_limiter.hpp>
#include <fcppt/config/external_begin.hpp>
#include <chrono>
#include <thread>
#include <fcppt/config/external_end.hpp>

sge::timer::scoped_frame_limiter::scoped_frame_limiter(ticks_per_second const _desired_fps)
    : before_frame_(clock_type::now()),
      minimum_frame_length_(
          std::chrono::duration_cast<clock_type::duration>(std::chrono::seconds(1)) /
          static_cast<clock_type::rep>(_desired_fps))
{
}

sge::timer::scoped_frame_limiter::~scoped_frame_limiter()
{
  clock_type::duration const diff(clock_type::now() - before_frame_);

  if (diff > minimum_frame_length_)
  {
    return;
  }

  std::this_thread::sleep_for(minimum_frame_length_ - diff);
}
