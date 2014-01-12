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


#ifndef SGE_SRC_IMAGE_COLOR_DYNAMIC_ALGORITHM_CAC_CHOOSE_HPP_INCLUDED
#define SGE_SRC_IMAGE_COLOR_DYNAMIC_ALGORITHM_CAC_CHOOSE_HPP_INCLUDED

#include <sge/image/color/invalid_convert.hpp>
#include <sge/src/image/color/dynamic/algorithm/cac/function.hpp>
#include <sge/src/image/color/dynamic/view/color_format.hpp>
#include <mizuiro/color/conversion/same_to_same.hpp>


namespace sge
{
namespace image
{
namespace color
{
namespace dynamic
{
namespace algorithm
{
namespace cac
{

template<
	typename SourceFormat,
	typename DestFormat
>
sge::image::color::dynamic::algorithm::cac::function<
	SourceFormat,
	DestFormat
>
choose(
	SourceFormat const &_source,
	DestFormat const &_dest
)
{
	if(
		sge::image::color::dynamic::view::color_format(
			_source
		).layout_type
		!=
		sge::image::color::dynamic::view::color_format(
			_dest
		).layout_type
	)
		throw sge::image::color::invalid_convert(
			sge::image::color::dynamic::view::color_format(
				_source
			).color_format,
			sge::image::color::dynamic::view::color_format(
				_dest
			).color_format
		);

	return
		&mizuiro::color::conversion::same_to_same<
			typename DestFormat::color_format,
			sge::image::color::dynamic::algorithm::cac::source<
				SourceFormat
			>
		>;
}

}
}
}
}
}
}

#endif
