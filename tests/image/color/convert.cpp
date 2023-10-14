//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/image/mizuiro_color_traits.hpp> // NOLINT(misc-include-cleaner)
#include <sge/image/color/a8_format.hpp>
#include <sge/image/color/bgra8_format.hpp>
#include <sge/image/color/is_convertible_v.hpp>
#include <sge/image/color/rgba8_format.hpp>

int main()
{
  static_assert(
      sge::image::color::
          is_convertible_v<sge::image::color::rgba8_format, sge::image::color::bgra8_format>,
      "rgba8 not convertible to bgra8");

  static_assert(
      !sge::image::color::
          is_convertible_v<sge::image::color::a8_format, sge::image::color::bgra8_format>,
      "a8 should not be convertible to bgra8");
}
