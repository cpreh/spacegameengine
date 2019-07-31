//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/font/height.hpp>
#include <sge/font/metrics.hpp>
#include <sge/font/unit.hpp>
#include <sge/gdifont/device_context_fwd.hpp>
#include <sge/gdifont/get_text_metrics.hpp>
#include <sge/gdifont/include_windows.hpp>
#include <sge/gdifont/make_metrics.hpp>
#include <sge/gdifont/scoped_select.hpp>
#include <fcppt/cast/size.hpp>


sge::font::metrics const
sge::gdifont::make_metrics(
	sge::gdifont::device_context const &_device_context,
	HFONT const _font
)
{
	sge::gdifont::scoped_select const selection(
		_device_context,
		_font
	);

	TEXTMETRIC const metric(
		sge::gdifont::get_text_metrics(
			_device_context
		)
	);

	return
		sge::font::metrics(
			sge::font::height(
				fcppt::cast::size<
					sge::font::unit
				>(
					metric.tmHeight
				)
			)
		);
}
