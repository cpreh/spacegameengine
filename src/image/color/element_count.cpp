/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2014 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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
	sge::image::color::format const _format
)
{
	switch(
		_format
	)
	{
	case sge::image::color::format::a8:
	case sge::image::color::format::l8:
	case sge::image::color::format::r32f:
		return 1;
	case sge::image::color::format::la8:
		return 2;
	case sge::image::color::format::rgb8:
	case sge::image::color::format::bgr8:
	case sge::image::color::format::rgb32f:
	case sge::image::color::format::bgr32f:
	case sge::image::color::format::srgb8:
	case sge::image::color::format::sbgr8:
		return 3;
	case sge::image::color::format::rgba8:
	case sge::image::color::format::rgbx8:
	case sge::image::color::format::bgra8:
	case sge::image::color::format::bgrx8:
	case sge::image::color::format::rgba32f:
	case sge::image::color::format::bgra32f:
	case sge::image::color::format::srgba8:
	case sge::image::color::format::sbgra8:
		return 4;
	}

	FCPPT_ASSERT_UNREACHABLE;
}
