//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/font/draw/color_format.hpp>
#include <sge/image/color/format.hpp>
#include <sge/image/color/optional_format.hpp>
#include <fcppt/const.hpp>
#include <fcppt/optional/from.hpp>

sge::image::color::format
sge::font::draw::color_format(sge::image::color::optional_format const &_color_format)
{
  return fcppt::optional::from(_color_format, fcppt::const_(sge::image::color::format::a8));
}
