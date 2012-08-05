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


#include <sge/font/align_h.hpp>
#include <sge/pango/convert/alignment.hpp>
#include <fcppt/assert/unreachable.hpp>
#include <fcppt/config/external_begin.hpp>
#include <pango/pango-layout.h>
#include <fcppt/config/external_end.hpp>


PangoAlignment
sge::pango::convert::alignment(
	sge::font::align_h::type const _alignment
)
{
	switch(
		_alignment
	)
	{
	case sge::font::align_h::left:
		return PANGO_ALIGN_LEFT;
	case sge::font::align_h::center:
		return PANGO_ALIGN_CENTER;
	case sge::font::align_h::right:
		return PANGO_ALIGN_RIGHT;
	}

	FCPPT_ASSERT_UNREACHABLE;
}
