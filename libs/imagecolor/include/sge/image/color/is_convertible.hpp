//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_IMAGE_COLOR_IS_CONVERTIBLE_HPP_INCLUDED
#define SGE_IMAGE_COLOR_IS_CONVERTIBLE_HPP_INCLUDED

#include <mizuiro/color/format/same_spaces.hpp>
#include <mizuiro/color/space/rgb.hpp>
#include <mizuiro/color/space/srgb.hpp>
#include <mizuiro/color/types/space.hpp>
#include <fcppt/config/external_begin.hpp>
#include <type_traits>
#include <fcppt/config/external_end.hpp>


namespace sge::image::color
{

// TODO(philipp): Remove this
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

#endif
