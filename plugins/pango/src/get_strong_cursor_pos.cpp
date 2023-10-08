//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/pango/get_strong_cursor_pos.hpp>
#include <fcppt/config/external_begin.hpp>
#include <pango/pango-layout.h>
#include <pango/pango-types.h>
#include <fcppt/config/external_end.hpp>

PangoRectangle sge::pango::get_strong_cursor_pos(PangoLayout &_layout, int const _index)
{
  PangoRectangle strong_pos;

  ::pango_layout_get_cursor_pos(&_layout, _index, &strong_pos, nullptr);

  return strong_pos;
}
