/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2012 Carl Philipp Reh (sefi@s-e-f-i.de)

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU Lesser General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
*/


#include <sge/font/rect.hpp>
#include <sge/pango/ink_rect.hpp>
#include <sge/pango/no_multi_line.hpp>
#include <sge/pango/convert/from_rect.hpp>
#include <fcppt/null_ptr.hpp>
#include <fcppt/config/external_begin.hpp>
#include <pango/pango-layout.h>
#include <fcppt/config/external_end.hpp>


sge::font::rect const
sge::pango::ink_rect(
	PangoLayout &_layout,
	sge::pango::no_multi_line const _no_multi_line
)
{
	PangoRectangle result;

	if(
		_no_multi_line.get()
	)
	{
		PangoLayoutLine *const line(
			::pango_layout_get_line(
				&_layout,
				0
			)
		);

		if(
			line == fcppt::null_ptr()
		)
			return sge::font::rect::null();

		::pango_layout_line_get_pixel_extents(
			line,
			&result,
			fcppt::null_ptr()
		);
	}
	else
		::pango_layout_get_pixel_extents(
			&_layout,
			&result,
			fcppt::null_ptr()
		);

	return
		sge::pango::convert::from_rect(
			result
		);
}
