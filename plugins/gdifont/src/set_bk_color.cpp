//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/font/exception.hpp>
#include <sge/gdifont/device_context.hpp>
#include <sge/gdifont/include_windows.hpp>
#include <sge/gdifont/set_bk_color.hpp>
#include <fcppt/text.hpp>


void
sge::gdifont::set_bk_color(
	sge::gdifont::device_context const &_device_context,
	COLORREF const _color
)
{
	if(
		::SetBkColor(
			_device_context.get(),
			_color
		)
		==
		CLR_INVALID
	)
		throw sge::font::exception(
			FCPPT_TEXT("SetBkColor failed")
		);
}
