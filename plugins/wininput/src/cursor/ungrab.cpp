//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/wininput/cursor/clip.hpp>
#include <sge/wininput/cursor/release_capture.hpp>
#include <sge/wininput/cursor/show.hpp>
#include <sge/wininput/cursor/ungrab.hpp>
#include <awl/backends/windows/optional_rect.hpp>

void sge::wininput::cursor::ungrab()
{
  sge::wininput::cursor::release_capture();

  sge::wininput::cursor::clip(awl::backends::windows::optional_rect());

  sge::wininput::cursor::show(true);
}
