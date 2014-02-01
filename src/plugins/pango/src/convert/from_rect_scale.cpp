/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2013 Carl Philipp Reh (sefi@s-e-f-i.de)

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
#include <sge/pango/convert/from_rect_scale.hpp>
#include <sge/pango/convert/from_unit.hpp>
#include <fcppt/config/external_begin.hpp>
#include <pango/pango-types.h>
#include <fcppt/config/external_end.hpp>


sge::font::rect const
sge::pango::convert::from_rect_scale(
	PangoRectangle const &_rect
)
{
	return
		sge::font::rect(
			sge::font::rect::vector(
				sge::pango::convert::from_unit(
					_rect.x
				),
				sge::pango::convert::from_unit(
					_rect.y
				)
			),
			sge::font::rect::dim(
				sge::pango::convert::from_unit(
					_rect.width
				),
				sge::pango::convert::from_unit(
					_rect.height
				)
			)
		);
}
