//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/wininput/cursor/show.hpp>
#include <awl/backends/windows/windows.hpp>

void sge::wininput::cursor::show(bool const _visible) { ::ShowCursor(_visible ? TRUE : FALSE); }
