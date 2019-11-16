//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_IMAGE_VIEW_BASIC_ELEMENTS_HPP_INCLUDED
#define SGE_IMAGE_VIEW_BASIC_ELEMENTS_HPP_INCLUDED

#include <sge/image/traits/image/color_tag.hpp>
#include <sge/image/traits/image/dimension.hpp>
#include <sge/image/traits/pixel/static_formats.hpp>
#include <sge/image/view/basic_format_c.hpp>
#include <sge/image/view/mizuiro_type.hpp>
#include <fcppt/config/external_begin.hpp>
#include <metal/lambda/always.hpp>
#include <metal/lambda/arg.hpp>
#include <metal/lambda/bind.hpp>
#include <metal/lambda/lambda.hpp>
#include <metal/list/transform.hpp>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace image
{
namespace view
{

template<
	typename Tag,
	typename Constness
>
using
basic_elements
=
metal::transform<
	metal::bind<
		metal::lambda<
			sge::image::view::mizuiro_type
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
		>,
		metal::always<
			Constness
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
