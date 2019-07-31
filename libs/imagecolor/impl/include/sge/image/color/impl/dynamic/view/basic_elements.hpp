//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_IMAGE_COLOR_IMPL_DYNAMIC_VIEW_BASIC_ELEMENTS_HPP_INCLUDED
#define SGE_IMAGE_COLOR_IMPL_DYNAMIC_VIEW_BASIC_ELEMENTS_HPP_INCLUDED

#include <sge/image/integral_size.hpp>
#include <sge/image/size_type.hpp>
#include <sge/image/color/impl/dynamic/format/all.hpp>
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
namespace color
{
namespace impl
{
namespace dynamic
{
namespace view
{

template<
	sge::image::size_type Dim,
	typename Constness
>
using
basic_elements
=
brigand::transform<
	sge::image::color::impl::dynamic::format::all,
	brigand::bind<
		sge::image::view::mizuiro_type,
		brigand::bind<
			sge::image::view::basic_format_c,
			brigand::pin<
				sge::image::integral_size<
					Dim
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
}
}
}

#endif
