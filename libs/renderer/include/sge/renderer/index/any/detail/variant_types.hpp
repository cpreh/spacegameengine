//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_RENDERER_INDEX_ANY_DETAIL_VARIANT_TYPES_HPP_INCLUDED
#define SGE_RENDERER_INDEX_ANY_DETAIL_VARIANT_TYPES_HPP_INCLUDED

#include <sge/renderer/index/any/detail/make_view_element.hpp>
#include <sge/renderer/index/dynamic/format.hpp>
#include <fcppt/mpl/arg.hpp>
#include <fcppt/mpl/bind.hpp>
#include <fcppt/mpl/constant.hpp>
#include <fcppt/mpl/lambda.hpp>
#include <fcppt/mpl/list/enum_range.hpp>
#include <fcppt/mpl/list/map.hpp>


namespace sge::renderer::index::any::detail
{

template<
	typename Constness
>
using
variant_types
=
fcppt::mpl::list::map<
	fcppt::mpl::list::enum_range<
		sge::renderer::index::dynamic::format
	>,
	fcppt::mpl::bind<
		fcppt::mpl::lambda<
			sge::renderer::index::any::detail::make_view_element
		>,
		fcppt::mpl::arg<1>,
		fcppt::mpl::constant<
			Constness
		>
	>
>;

}

#endif
