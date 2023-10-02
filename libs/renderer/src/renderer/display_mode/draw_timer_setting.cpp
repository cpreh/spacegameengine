//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/renderer/display_mode/draw_timer_setting.hpp>
#include <sge/renderer/display_mode/refresh_rate.hpp>
#include <awl/timer/duration.hpp>
#include <awl/timer/period.hpp>
#include <awl/timer/setting.hpp>
#include <awl/timer/setting_no_delay.hpp>
#include <fcppt/cast/int_to_float.hpp>
#include <fcppt/config/external_begin.hpp>
#include <chrono>
#include <fcppt/config/external_end.hpp>

awl::timer::setting sge::renderer::display_mode::draw_timer_setting(
    sge::renderer::display_mode::refresh_rate const _rate)
{
  return awl::timer::setting_no_delay(
      awl::timer::period{std::chrono::duration_cast<awl::timer::duration>(
          std::chrono::seconds{1} / fcppt::cast::int_to_float<float>(_rate.get()))});
}
