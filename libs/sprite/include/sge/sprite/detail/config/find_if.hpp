//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_SPRITE_DETAIL_CONFIG_FIND_IF_HPP_INCLUDED
#define SGE_SPRITE_DETAIL_CONFIG_FIND_IF_HPP_INCLUDED

#include <sge/sprite/detail/config/find_if_impl.hpp>


namespace sge::sprite::detail::config
{

template<
	typename Elements,
	template<
		typename
	> class Predicate
>
using
find_if
=
typename
sge::sprite::detail::config::find_if_impl<
	Elements,
	Predicate
>::type;

}

#endif
