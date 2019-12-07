//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_IMAGE_STORE_ELEMENTS_HPP_INCLUDED
#define SGE_IMAGE_STORE_ELEMENTS_HPP_INCLUDED

#include <sge/image/store/basic.hpp>
#include <sge/image/traits/image/color_tag.hpp>
#include <sge/image/traits/image/dimension.hpp>
#include <sge/image/traits/pixel/static_formats.hpp>
#include <sge/image/view/basic_format_c.hpp>
#include <fcppt/config/external_begin.hpp>
#include <metal.hpp>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace image
{
namespace store
{

template<
	typename Tag
>
using
elements
=
metal::transform<
	metal::bind<
		metal::lambda<
			sge::image::store::basic
		>,
		metal::bind<
			metal::lambda<
				sge::image::view::basic_format_c
			>,
			metal::always<
				sge::image::traits::image::dimension<
					Tag
				>
			>,
			metal::_1
		>
	>,
	sge::image::traits::pixel::static_formats<
		sge::image::traits::image::color_tag<
			Tag
		>
	>
>;

}
}
}

#endif
