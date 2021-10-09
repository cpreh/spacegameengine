//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/renderer/display_mode/draw_timer_setting.hpp>
#include <sge/renderer/display_mode/draw_timer_setting_opt.hpp>
#include <sge/renderer/display_mode/object.hpp>
#include <sge/renderer/display_mode/optional_object.hpp>
#include <sge/renderer/display_mode/refresh_rate.hpp>
#include <awl/timer/setting.hpp>
#include <fcppt/text.hpp>
#include <fcppt/log/info.hpp>
#include <fcppt/log/object_fwd.hpp>
#include <fcppt/log/out.hpp>
#include <fcppt/log/warning.hpp>
#include <fcppt/optional/bind.hpp>
#include <fcppt/optional/from.hpp>
#include <fcppt/optional/map.hpp>

awl::timer::setting sge::renderer::display_mode::draw_timer_setting_opt(
    fcppt::log::object &_log, sge::renderer::display_mode::optional_object const &_opt_display_mode)
{
  return fcppt::optional::from(
      fcppt::optional::bind(
          _opt_display_mode,
          [&_log](sge::renderer::display_mode::object const &_display_mode)
          {
            return fcppt::optional::map(
                _display_mode.refresh_rate(),
                [&_log](sge::renderer::display_mode::refresh_rate const _rate)
                {
                  awl::timer::setting const result{
                      sge::renderer::display_mode::draw_timer_setting(_rate)};

                  FCPPT_LOG_INFO(
                      _log,
                      fcppt::log::out << FCPPT_TEXT("Using draw interval of ")
                                      << result.period().get().count()
                                      << FCPPT_TEXT(" milliseconds"))

                  return result;
                });
          }),
      [&_log]
      {
        constexpr sge::renderer::display_mode::refresh_rate_value const default_fps{60};

        FCPPT_LOG_WARNING(
            _log,
            fcppt::log::out << FCPPT_TEXT("Cannot determine display refresh rate -")
                            << FCPPT_TEXT(" using a refresh rate of ") << default_fps
                            << FCPPT_TEXT('.'))

        return sge::renderer::display_mode::draw_timer_setting(
            sge::renderer::display_mode::refresh_rate{default_fps});
      });
}
