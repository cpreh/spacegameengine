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


#ifndef SGE_IMAGE_COLOR_IS_CONVERTIBLE_HPP_INCLUDED
#define SGE_IMAGE_COLOR_IS_CONVERTIBLE_HPP_INCLUDED

#include <mizuiro/color/format/same_spaces.hpp>
#include <mizuiro/color/space/rgb.hpp>
#include <mizuiro/color/space/srgb.hpp>
#include <mizuiro/color/types/space.hpp>
#include <fcppt/config/external_begin.hpp>
#include <type_traits>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace image
{
namespace color
{

// TODO: Remove this
template<
	typename SourceFormat,
	typename DestFormat
>
using is_convertible
=
std::disjunction<
	mizuiro::color::format::same_spaces<
		SourceFormat,
		DestFormat
	>,
	std::conjunction<
		std::is_same<
			mizuiro::color::types::space<
				DestFormat
			>,
			mizuiro::color::space::srgb
		>,
		std::is_same<
			mizuiro::color::types::space<
				SourceFormat
			>,
			mizuiro::color::space::rgb
		>
	>,
	std::conjunction<
		std::is_same<
			mizuiro::color::types::space<
				DestFormat
			>,
			mizuiro::color::space::rgb
		>,
		std::is_same<
			mizuiro::color::types::space<
				SourceFormat
			>,
			mizuiro::color::space::srgb
		>
	>
>;

}
}
}

#endif
