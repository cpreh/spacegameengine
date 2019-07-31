//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/pango/extents.hpp>
#include <sge/pango/get_extents.hpp>
#include <sge/pango/ink_rect.hpp>
#include <sge/pango/logical_rect.hpp>
#include <sge/pango/convert/from_rect.hpp>
#include <fcppt/config/external_begin.hpp>
#include <pango/pango-layout.h>
#include <fcppt/config/external_end.hpp>


sge::pango::extents
sge::pango::get_extents(
	PangoLayout &_layout
)
{
	PangoRectangle ink_result;

	PangoRectangle logical_result;

	::pango_layout_get_pixel_extents(
		&_layout,
		&ink_result,
		&logical_result
	);

	return
		sge::pango::extents(
			sge::pango::ink_rect(
				sge::pango::convert::from_rect(
					ink_result
				)
			),
			sge::pango::logical_rect(
				sge::pango::convert::from_rect(
					logical_result
				)
			)
		);
}
