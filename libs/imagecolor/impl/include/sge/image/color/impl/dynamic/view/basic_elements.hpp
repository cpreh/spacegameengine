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
#include <fcppt/mpl/arg.hpp>
#include <fcppt/mpl/bind.hpp>
#include <fcppt/mpl/constant.hpp>
#include <fcppt/mpl/lambda.hpp>
#include <fcppt/mpl/list/map.hpp>


namespace sge::image::color::impl::dynamic::view
{

template<
	sge::image::size_type Dim,
	typename Constness
>
using
basic_elements
=
fcppt::mpl::list::map<
	sge::image::color::impl::dynamic::format::all,
	fcppt::mpl::bind<
		fcppt::mpl::lambda<
			sge::image::view::mizuiro_type
		>,
		fcppt::mpl::bind<
			fcppt::mpl::lambda<
				sge::image::view::basic_format_c
			>,
			fcppt::mpl::constant<
				sge::image::integral_size<
					Dim
				>
			>,
			fcppt::mpl::arg<1>
		>,
		fcppt::mpl::constant<
			Constness
		>
	>
>;

}

#endif
