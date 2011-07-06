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


#ifndef SGE_IMAGE_DYNAMIC_ALGORITHM_CAC_CHOOSE_HPP_INCLUDED
#define SGE_IMAGE_DYNAMIC_ALGORITHM_CAC_CHOOSE_HPP_INCLUDED

#include "function.hpp"
#include "source.hpp"
#include "../../color/available_channels.hpp"
#include "../../color/c8_1_format.hpp"
#include <mizuiro/color/conversion/alpha_to_any.hpp>
#include <mizuiro/color/conversion/luminance_to_rgb.hpp>
#include <cstdlib>

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

#if 0
template<
	typename DestFormat
>
typename cac::function<
	dynamic::color::c8_1_format,
	DestFormat
>::type
choose(
	dynamic::color::c8_1_format const &_source_format
	DestFormat const &_dest_format
)
{
	switch(
		_source_format.layout[0]
	)
	case dynamic::color::available_channels::alpha:
		return
			&mizuiro::color::conversion::alpha_to_any<
				DestFormat,
				typename cac::source<
					dynamic::color::c8_1_format
				>::type
			>;
	case dynamic::color::available_channels::luminance:
		if(
			cac::is_rgb(
				_dest_format
			)
		)
			return
				&mizuiro::color::conversion::luminance_to_rgb<
					DestFormat,
					typename cac::source<
						dynamic::color::c8_1_format
					>::type
				>;
		else if(
			_dest_format.layout[0] == dynamic::color::available_channels::alpha
		)
			return
				&mizuiro::color::conversion::alpha_to_any<
					DestFormat,
					typename cac::source<
						dynamic::color::c8_1_format
					>::type
				>;
	case dynamic::color::available_channels::red:
	case dynamic::color::available_channels::green:
	case dynamic::color::available_channels::blue:
		break;
	}	

	std::abort();
}
#endif

template<
	typename SourceFormat,
	typename DestFormat
>
typename cac::function<
	SourceFormat,
	DestFormat
>::type
choose(
	SourceFormat const &,
	DestFormat const &
)
{
	// TODO:
	return 0;
}

}
}
}
}
}

#endif
