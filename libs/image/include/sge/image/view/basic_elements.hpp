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
#include <brigand/algorithms/transform.hpp>
#include <brigand/functions/lambda/apply.hpp>
#include <brigand/functions/lambda/bind.hpp>
#include <brigand/types/args.hpp>
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
brigand::transform<
	sge::image::traits::pixel::static_formats<
		sge::image::traits::image::color_tag<
			Tag
		>
	>,
	brigand::bind<
		sge::image::view::mizuiro_type,
		brigand::bind<
			sge::image::view::basic_format_c,
			brigand::pin<
				sge::image::traits::image::dimension<
					Tag
				>
			>,
			brigand::_1
		>,
		Constness
	>
>;

}
}
}

#endif
