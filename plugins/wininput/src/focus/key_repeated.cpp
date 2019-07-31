//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/wininput/focus/key_repeated.hpp>
#include <awl/backends/windows/lparam.hpp>
#include <awl/backends/windows/windows.hpp>
#include <fcppt/literal.hpp>


bool
sge::wininput::focus::key_repeated(
	awl::backends::windows::lparam const _lparam
)
{
	return
		(
			_lparam.get()
			&
			(
				fcppt::literal<
					LPARAM
				>(
					1
				)
				<<
				30u
			)
		)
		!=
		0;
}
