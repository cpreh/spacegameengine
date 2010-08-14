/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2010 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#include <sge/image/color/format_stride.hpp>
#include <sge/image/color/element_count.hpp>
#include <sge/image/exception.hpp>
#include <fcppt/text.hpp>
#include <boost/cstdint.hpp>

namespace
{

sge::image::size_type
base_size(
	sge::image::color::format::type const _format
)
{
	namespace format = sge::image::color::format;

	switch(_format)
	{
	case format::gray8:
	case format::alpha8:
		return sizeof(boost::uint8_t);
	case format::rgba8:
	case format::argb8:
	case format::bgra8:
		return sizeof(boost::uint8_t);
	case format::rgb8:
		return sizeof(boost::uint8_t);
	case format::rgba32f:
	case format::argb32f:
	case format::bgra32f:
		return sizeof(float);
	case format::size:
		break;
	}

	throw sge::image::exception(
		FCPPT_TEXT("Invalid format in format_stride()!")
	);
}

}

sge::image::size_type
sge::image::color::format_stride(
	format::type const _format
)
{
	return
		color::element_count(
			_format
		)
		* base_size(
			_format
		);
}
