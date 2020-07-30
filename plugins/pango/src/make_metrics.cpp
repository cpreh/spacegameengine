//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/font/height.hpp>
#include <sge/font/metrics.hpp>
#include <sge/pango/make_metrics.hpp>
#include <fcppt/config/external_begin.hpp>
#include <pango/pango-layout.h>
#include <fcppt/config/external_end.hpp>


sge::font::metrics
sge::pango::make_metrics(
	PangoLayout &_layout
)
{
	int height{};

	::pango_layout_get_pixel_size(
		&_layout,
		nullptr,
		&height
	);

	return
		sge::font::metrics(
			sge::font::height(
				height
			)
		);
}
