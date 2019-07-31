//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_IMAGE_COLOR_CONVERT_HPP_INCLUDED
#define SGE_IMAGE_COLOR_CONVERT_HPP_INCLUDED

#include <sge/image/color/is_convertible.hpp>
#include <sge/image/pixel/mizuiro_type.hpp>
#include <mizuiro/color/convert_static.hpp>


namespace sge
{
namespace image
{
namespace color
{

template<
	typename DestFormat,
	typename Src
>
sge::image::pixel::mizuiro_type<
	DestFormat
>
convert(
	Src const &_src
)
{
	static_assert(
		sge::image::color::is_convertible<
			typename Src::format,
			DestFormat
		>::value,
		"Formats are not convertible"
	);

	return
		mizuiro::color::convert_static::convert<
			DestFormat
		>(
			_src
		);
}

}
}
}

#endif
