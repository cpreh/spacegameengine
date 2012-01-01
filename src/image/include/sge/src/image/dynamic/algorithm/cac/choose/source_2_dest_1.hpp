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


#ifndef SGE_SRC_IMAGE_DYNAMIC_ALGORITHM_CAC_CHOOSE_SOURCE_2_DEST_1_HPP_INCLUDED
#define SGE_SRC_IMAGE_DYNAMIC_ALGORITHM_CAC_CHOOSE_SOURCE_2_DEST_1_HPP_INCLUDED

#include <sge/src/image/dynamic/algorithm/cac/function.hpp>
#include <sge/src/image/dynamic/algorithm/cac/source.hpp>
#include <sge/src/image/dynamic/algorithm/cac/choose/format_has_size.hpp>
#include <sge/src/image/dynamic/algorithm/cac/choose/no_match.hpp>
#include <sge/src/image/dynamic/color/available_channels.hpp>
#include <sge/src/image/dynamic/view/format_channel.hpp>
#include <mizuiro/color/conversion/any_to_alpha.hpp>
#include <mizuiro/color/conversion/luminance_to_rgb.hpp>
#include <mizuiro/color/conversion/same_to_same.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/mpl/and.hpp>
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
		cac::format_has_size<
			DestFormat,
			1
		>
	>,
	typename cac::function<
		SourceFormat,
		DestFormat
	>::type
>::type
choose(
	SourceFormat const &,
	DestFormat const &_dest_format
)
{
	switch(
		dynamic::view::format_channel(
			_dest_format,
			0
		)
	)
	{
	// la8 to a8
	case dynamic::color::available_channels::alpha:
		return
			&mizuiro::color::conversion::any_to_alpha<
				typename DestFormat::color_format,
				typename cac::source<
					SourceFormat
				>::type
			>;
	// la8 to l8
	case dynamic::color::available_channels::luminance:
		return
			&mizuiro::color::conversion::same_to_same<
				typename DestFormat::color_format,
				typename cac::source<
					SourceFormat
				>::type
			>;
	// la8 to r32f
	case dynamic::color::available_channels::red:
		return
			&mizuiro::color::conversion::luminance_to_rgb<
				typename DestFormat::color_format,
				typename cac::source<
					SourceFormat
				>::type
			>;
	case dynamic::color::available_channels::green:
	case dynamic::color::available_channels::blue:
	case dynamic::color::available_channels::undefined:
	case dynamic::color::available_channels::size:
		break;
	}

	SGE_SRC_IMAGE_DYNAMIC_ALGORITHM_CAC_CHOOSE_NO_MATCH;
}

}
}
}
}
}

#endif
