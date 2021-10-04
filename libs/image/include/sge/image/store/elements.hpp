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
#include <fcppt/mpl/arg.hpp>
#include <fcppt/mpl/bind.hpp>
#include <fcppt/mpl/constant.hpp>
#include <fcppt/mpl/lambda.hpp>
#include <fcppt/mpl/list/map.hpp>


namespace sge::image::store
{

template<
	typename Tag
>
using
elements
=
fcppt::mpl::list::map<
	sge::image::traits::pixel::static_formats<
		sge::image::traits::image::color_tag<
			Tag
		>
	>,
	fcppt::mpl::bind<
		fcppt::mpl::lambda<
			sge::image::store::basic
		>,
		fcppt::mpl::bind<
			fcppt::mpl::lambda<
				sge::image::view::basic_format_c
			>,
			fcppt::mpl::constant<
				sge::image::traits::image::dimension<
					Tag
				>
			>,
			fcppt::mpl::arg<1>
		>
	>
>;

}

#endif
