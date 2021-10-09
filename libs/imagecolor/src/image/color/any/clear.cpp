//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/image/color/a8.hpp>
#include <sge/image/color/format.hpp>
#include <sge/image/color/l8.hpp>
#include <sge/image/color/la8.hpp>
#include <sge/image/color/predef.hpp>
#include <sge/image/color/r32f.hpp>
#include <sge/image/color/sbgra8.hpp>
#include <sge/image/color/srgba8.hpp>
#include <sge/image/color/any/clear.hpp>
#include <sge/image/color/any/object.hpp>
#include <sge/image/color/init/alpha.hpp>
#include <sge/image/color/init/blue.hpp>
#include <sge/image/color/init/green.hpp>
#include <sge/image/color/init/luminance.hpp>
#include <sge/image/color/init/red.hpp>
#include <fcppt/assert/unreachable.hpp>

sge::image::color::any::object
sge::image::color::any::clear(sge::image::color::format const _format)
{
  // TODO(philipp): Make this more generic
  switch (_format)
  {
  case sge::image::color::format::a8:
    return sge::image::color::any::object(
        sge::image::color::a8(sge::image::color::init::alpha() %= 0.));
  case sge::image::color::format::l8:
    return sge::image::color::any::object(
        sge::image::color::l8(sge::image::color::init::luminance() %= 0.));
  case sge::image::color::format::r32f:
    return sge::image::color::any::object(
        sge::image::color::r32f(sge::image::color::init::red() %= 0.));
  case sge::image::color::format::la8:
    return sge::image::color::any::object(sge::image::color::la8(
        (sge::image::color::init::alpha() %= 0.)(sge::image::color::init::luminance() %= 0.)));
  case sge::image::color::format::rgb8:
  case sge::image::color::format::bgr8:
  case sge::image::color::format::rgbx8:
  case sge::image::color::format::bgrx8:
  case sge::image::color::format::rgba8:
  case sge::image::color::format::bgra8:
  case sge::image::color::format::rgb32f:
  case sge::image::color::format::bgr32f:
  case sge::image::color::format::rgba32f:
  case sge::image::color::format::bgra32f:
    return sge::image::color::any::object(sge::image::color::predef::transparent());
  case sge::image::color::format::srgb8:
  case sge::image::color::format::srgba8:
    return sge::image::color::any::object(sge::image::color::srgba8(
        (sge::image::color::init::red() %= 0.)(sge::image::color::init::green() %= 0.)(
            sge::image::color::init::blue() %= 0.)(sge::image::color::init::alpha() %= 0.)));
  case sge::image::color::format::sbgr8:
  case sge::image::color::format::sbgra8:
    return sge::image::color::any::object(sge::image::color::sbgra8(
        (sge::image::color::init::red() %= 0.)(sge::image::color::init::green() %= 0.)(
            sge::image::color::init::blue() %= 0.)(sge::image::color::init::alpha() %= 0.)));
  }

  FCPPT_ASSERT_UNREACHABLE;
}
