//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_IMAGE_PIXEL_ELEMENTS_HPP_INCLUDED
#define SGE_IMAGE_PIXEL_ELEMENTS_HPP_INCLUDED

#include <sge/image/pixel/mizuiro_type.hpp>
#include <sge/image/traits/pixel/static_formats.hpp>
#include <fcppt/mpl/lambda.hpp>
#include <fcppt/mpl/list/map.hpp>


namespace sge
{
namespace image
{
namespace pixel
{

template<
	typename Tag
>
using
elements
=
fcppt::mpl::list::map<
	sge::image::traits::pixel::static_formats<
		Tag
	>,
	fcppt::mpl::lambda<
		sge::image::pixel::mizuiro_type
	>
>;

}
}
}

#endif
