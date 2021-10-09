//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/opengl/xrandr/refresh_rate_from_mode.hpp>
#include <sge/renderer/display_mode/optional_refresh_rate.hpp>
#include <sge/renderer/display_mode/refresh_rate.hpp>
#include <fcppt/strong_typedef_construct_cast.hpp>
#include <fcppt/cast/float_to_int.hpp>
#include <fcppt/cast/int_to_float.hpp>
#include <fcppt/cast/size_fun.hpp>
#include <fcppt/cast/to_unsigned.hpp>
#include <fcppt/config/external_begin.hpp>
#include <X11/extensions/Xrandr.h>
#include <cmath>
#include <type_traits>
#include <fcppt/config/external_end.hpp>

sge::renderer::display_mode::optional_refresh_rate
sge::opengl::xrandr::refresh_rate_from_mode(XRRModeInfo const &_info)
{
  using unsigned_type = unsigned long long;

  unsigned_type const denom(_info.hTotal * _info.vTotal);

  using float_type = double;

  using signed_type = std::make_signed_t<unsigned_type>;

  return denom == 0U ? sge::renderer::display_mode::optional_refresh_rate()
                     : sge::renderer::display_mode::optional_refresh_rate(
                           fcppt::strong_typedef_construct_cast<
                               sge::renderer::display_mode::refresh_rate,
                               fcppt::cast::size_fun>(fcppt::cast::to_unsigned(
                               fcppt::cast::float_to_int<signed_type>(std::round(
                                   fcppt::cast::int_to_float<float_type>(_info.dotClock) /
                                   fcppt::cast::int_to_float<float_type>(denom))))));
}
