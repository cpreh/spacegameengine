//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/font/exception.hpp>
#include <sge/font/string.hpp>
#include <sge/gdifont/device_context.hpp>
#include <sge/gdifont/draw_text.hpp>
#include <sge/gdifont/include_windows.hpp>
#include <fcppt/text.hpp>
#include <fcppt/cast/size.hpp>
#include <fcppt/cast/to_signed.hpp>

RECT sge::gdifont::draw_text(
    sge::gdifont::device_context const &_device_context,
    sge::font::string const &_string,
    RECT _rect,
    UINT const _format)
{
  int const result{DrawTextW(
      _device_context.get(),
      _string.data(),
      fcppt::cast::size<int>(fcppt::cast::to_signed(_string.size())),
      &_rect,
      _format)};

  if (result == 0)
    throw sge::font::exception{FCPPT_TEXT("DrawText failed!")};

  _rect.bottom = _rect.top + result;

  return _rect;
}
