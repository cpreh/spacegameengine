//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_IMAGE_IMPL_VIEW_TO_STATIC_FORMAT_HPP_INCLUDED
#define SGE_IMAGE_IMPL_VIEW_TO_STATIC_FORMAT_HPP_INCLUDED

#include <sge/image/impl/pixel/to_static_format.hpp>
#include <sge/image/traits/image/color_tag.hpp>
#include <sge/image/traits/image/dimension.hpp>
#include <sge/image/view/basic_format.hpp>


namespace sge::image::impl::view
{

template<
	typename Tag,
	typename FormatEnum
>
using
to_static_format
=
sge::image::view::basic_format<
	sge::image::traits::image::dimension<
		Tag
	>::value,
	sge::image::impl::pixel::to_static_format<
		sge::image::traits::image::color_tag<
			Tag
		>,
		FormatEnum
	>
>;

}

#endif
