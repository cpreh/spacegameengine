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


#ifndef SGE_SRC_IMAGE_DYNAMIC_ALGORITHM_CAC_CHOOSE_SOURCE_2_DEST_3_4_HPP_INCLUDED
#define SGE_SRC_IMAGE_DYNAMIC_ALGORITHM_CAC_CHOOSE_SOURCE_2_DEST_3_4_HPP_INCLUDED

#include <sge/src/image/dynamic/algorithm/cac/choose/format_has_size.hpp>
#include <sge/src/image/dynamic/algorithm/cac/function.hpp>
#include <sge/src/image/dynamic/algorithm/cac/source.hpp>
#include <mizuiro/color/conversion/luminance_to_rgb.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/mpl/and.hpp>
#include <boost/mpl/or.hpp>
#include <boost/utility/enable_if.hpp>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace image
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
typename boost::enable_if<
	boost::mpl::and_<
		cac::format_has_size<
			SourceFormat,
			2
		>,
		boost::mpl::or_<
			cac::format_has_size<
				DestFormat,
				3
			>,
			cac::format_has_size<
				DestFormat,
				4
			>
		>
	>,
	typename cac::function<
		SourceFormat,
		DestFormat
	>::type
>::type
choose(
	SourceFormat const &,
	DestFormat const &
)
{
	// la8 to rgb
	return
		&mizuiro::color::conversion::luminance_to_rgb<
			typename DestFormat::color_format,
			typename cac::source<
				SourceFormat
			>::type
		>;
}

}
}
}
}
}

#endif
