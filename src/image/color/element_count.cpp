/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2011 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#include <sge/image/size_type.hpp>
#include <sge/image/color/element_count.hpp>
#include <sge/image/color/format.hpp>
#include <fcppt/assert/unreachable.hpp>


sge::image::size_type
sge::image::color::element_count(
	format::type const _format
)
{
	switch(
		_format
	)
	{
	case format::a8:
	case format::l8:
		return 1;
	case format::la8:
		return 2;
	case format::rgb8:
	case format::bgr8:
	case format::rgb32f:
	case format::bgr32f:
		return 3;
	case format::rgba8:
	case format::rgbx8:
	case format::bgra8:
	case format::bgrx8:
	case format::rgba32f:
	case format::bgra32f:
		return 4;
	case format::size:
		break;
	}

	FCPPT_ASSERT_UNREACHABLE;
}
