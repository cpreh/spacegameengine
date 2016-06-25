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


#include <sge/font/align_h/center_fwd.hpp>
#include <sge/font/align_h/left_fwd.hpp>
#include <sge/font/align_h/right_fwd.hpp>
#include <sge/font/align_h/variant.hpp>
#include <sge/pango/convert/alignment.hpp>
#include <fcppt/variant/match.hpp>
#include <fcppt/config/external_begin.hpp>
#include <pango/pango-layout.h>
#include <fcppt/config/external_end.hpp>


PangoAlignment
sge::pango::convert::alignment(
	sge::font::align_h::variant const &_alignment
)
{
	return
		fcppt::variant::match(
			_alignment,
			[](
				sge::font::align_h::left const &
			)
			{
				return
					PANGO_ALIGN_LEFT;
			},
			[](
				sge::font::align_h::center const &
			)
			{
				return
					PANGO_ALIGN_CENTER;
			},
			[](
				sge::font::align_h::right const &
			)
			{
				return
					PANGO_ALIGN_RIGHT;
			}
		);
}
