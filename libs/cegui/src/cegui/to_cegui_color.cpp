//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/cegui/to_cegui_color.hpp>
#include <sge/image/color/rgba32f.hpp>
#include <sge/image/color/rgba32f_format.hpp>
#include <sge/image/color/any/convert.hpp>
#include <sge/image/color/any/object_fwd.hpp>
#include <mizuiro/color/channel/alpha.hpp>
#include <mizuiro/color/channel/blue.hpp>
#include <mizuiro/color/channel/green.hpp>
#include <mizuiro/color/channel/red.hpp>
#include <fcppt/config/external_begin.hpp>
#include <CEGUI/Colour.h>
#include <fcppt/config/external_end.hpp>

CEGUI::Colour sge::cegui::to_cegui_color(sge::image::color::any::object const &_color)
{
  sge::image::color::rgba32f const dest(
      sge::image::color::any::convert<sge::image::color::rgba32f_format>(_color));

  return CEGUI::Colour(
      dest.get(mizuiro::color::channel::red()),
      dest.get(mizuiro::color::channel::green()),
      dest.get(mizuiro::color::channel::blue()),
      dest.get(mizuiro::color::channel::alpha()));
}
