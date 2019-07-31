//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/wininput/cursor/get_pos.hpp>
#include <awl/backends/windows/optional_point.hpp>
#include <awl/backends/windows/windows.hpp>


awl::backends::windows::optional_point const
sge::wininput::cursor::get_pos()
{
	POINT ret;

	return
		::GetCursorPos(
			&ret
		)
		== 0
		?
			awl::backends::windows::optional_point()
		:
			awl::backends::windows::optional_point(
				ret
			)
		;
}
