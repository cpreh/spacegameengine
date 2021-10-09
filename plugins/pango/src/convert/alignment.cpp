//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/font/align_h/center_fwd.hpp>
#include <sge/font/align_h/left_fwd.hpp>
#include <sge/font/align_h/right_fwd.hpp>
#include <sge/font/align_h/variant.hpp>
#include <sge/pango/convert/alignment.hpp>
#include <fcppt/variant/match.hpp>
#include <fcppt/config/external_begin.hpp>
#include <pango/pango-layout.h>
#include <fcppt/config/external_end.hpp>

PangoAlignment sge::pango::convert::alignment(sge::font::align_h::variant const &_alignment)
{
  return fcppt::variant::match(
      _alignment,
      [](sge::font::align_h::left const &) { return PANGO_ALIGN_LEFT; },
      [](sge::font::align_h::center const &) { return PANGO_ALIGN_CENTER; },
      [](sge::font::align_h::right const &) { return PANGO_ALIGN_RIGHT; });
}
