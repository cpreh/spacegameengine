/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2016 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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


#include <sge/font/vector.hpp>
#include <sge/pango/index.hpp>
#include <sge/pango/optional_index.hpp>
#include <sge/pango/xy_to_index.hpp>
#include <sge/pango/convert/to_unit.hpp>
#include <fcppt/config/external_begin.hpp>
#include <pango/pango-layout.h>
#include <fcppt/config/external_end.hpp>


sge::pango::optional_index
sge::pango::xy_to_index(
	PangoLayout &_layout,
	sge::font::vector const _pos
)
{
	int result;

	int trailing;

	return
		::pango_layout_xy_to_index(
			&_layout,
			sge::pango::convert::to_unit(
				_pos.x()
			),
			sge::pango::convert::to_unit(
				_pos.y()
			),
			&result,
			&trailing
		)
		==
		TRUE
		?
			sge::pango::optional_index{
				sge::pango::index{
					sge::pango::index::result_type{
						result
					},
					sge::pango::index::trailing_type{
						trailing
					}
				}
			}
		:
			sge::pango::optional_index{}
		;

}
