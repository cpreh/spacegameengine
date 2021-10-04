//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_SPRITE_DETAIL_CONFIG_CONTAINS_IF_HPP_INCLUDED
#define SGE_SPRITE_DETAIL_CONFIG_CONTAINS_IF_HPP_INCLUDED

#include <fcppt/mpl/lambda.hpp>
#include <fcppt/mpl/list/any_of.hpp>


namespace sge::sprite::detail::config
{

template<
	typename Elements,
	template<
		typename
	> class Predicate
>
using
contains_if
=
fcppt::mpl::list::any_of<
	Elements,
	fcppt::mpl::lambda<
		Predicate
	>
>;

}

#endif
