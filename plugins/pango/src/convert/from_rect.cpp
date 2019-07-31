//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/font/rect.hpp>
#include <sge/pango/convert/from_rect.hpp>
#include <fcppt/config/external_begin.hpp>
#include <pango/pango-types.h>
#include <fcppt/config/external_end.hpp>


sge::font::rect
sge::pango::convert::from_rect(
	PangoRectangle const &_rect
)
{
	return
		sge::font::rect(
			sge::font::rect::vector(
				_rect.x,
				_rect.y
			),
			sge::font::rect::dim(
				_rect.width,
				_rect.height
			)
		);
}
