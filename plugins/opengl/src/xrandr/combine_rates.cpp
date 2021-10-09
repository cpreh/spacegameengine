//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/opengl/xrandr/combine_rates.hpp>
#include <sge/renderer/display_mode/optional_refresh_rate.hpp>
#include <sge/renderer/display_mode/refresh_rate.hpp>
#include <fcppt/optional/combine.hpp>
#include <fcppt/config/external_begin.hpp>
#include <algorithm>
#include <fcppt/config/external_end.hpp>

sge::renderer::display_mode::optional_refresh_rate sge::opengl::xrandr::combine_rates(
    sge::renderer::display_mode::optional_refresh_rate const _opt_rate_a,
    sge::renderer::display_mode::optional_refresh_rate const _opt_rate_b)
{
  return fcppt::optional::combine(
      _opt_rate_a,
      _opt_rate_b,
      [](sge::renderer::display_mode::refresh_rate const _rate_a,
         sge::renderer::display_mode::refresh_rate const _rate_b)
      { return std::max(_rate_a, _rate_b); });
}
