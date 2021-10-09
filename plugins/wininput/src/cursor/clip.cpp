//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/wininput/cursor/clip.hpp>
#include <awl/backends/windows/optional_rect.hpp>
#include <awl/backends/windows/windows.hpp>
#include <fcppt/const.hpp>
#include <fcppt/optional/maybe.hpp>

bool sge::wininput::cursor::clip(awl::backends::windows::optional_rect const &_area)
{
  return ::ClipCursor(fcppt::optional::maybe(
             _area,
             fcppt::const_<RECT const *>(nullptr),
             [](RECT const &_rect) { return &_rect; })) != 0;
}
