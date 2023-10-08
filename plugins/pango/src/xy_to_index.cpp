//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/font/vector.hpp>
#include <sge/pango/index.hpp>
#include <sge/pango/optional_index.hpp>
#include <sge/pango/xy_to_index.hpp>
#include <sge/pango/convert/to_unit.hpp>
#include <fcppt/config/external_begin.hpp>
#include <glib/gmacros.h>
#include <pango/pango-layout.h>
#include <fcppt/config/external_end.hpp>

sge::pango::optional_index
sge::pango::xy_to_index(PangoLayout &_layout, sge::font::vector const &_pos)
{
  int result{};

  int trailing{};

  return ::pango_layout_xy_to_index(
             &_layout,
             sge::pango::convert::to_unit(_pos.x()),
             sge::pango::convert::to_unit(_pos.y()),
             &result,
             &trailing) == TRUE
             ? sge::pango::optional_index{sge::pango::index{
                   sge::pango::index::result_type{result},
                   sge::pango::index::trailing_type{trailing}}}
             : sge::pango::optional_index{};
}
