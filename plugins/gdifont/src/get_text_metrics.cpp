//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/font/exception.hpp>
#include <sge/gdifont/device_context.hpp>
#include <sge/gdifont/get_text_metrics.hpp>
#include <sge/gdifont/include_windows.hpp>
#include <fcppt/text.hpp>


TEXTMETRIC const
sge::gdifont::get_text_metrics(
	sge::gdifont::device_context const &_device_context
)
{
	TEXTMETRIC result;

	if(
		::GetTextMetrics(
			_device_context.get(),
			&result
		)
		==
		0
	)
		throw
			sge::font::exception(
				FCPPT_TEXT("GetTextMetrics failed")
			);

	return
		result;
}
