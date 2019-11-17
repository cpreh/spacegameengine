//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_SPRITE_DETAIL_CONFIG_CONTAINS_IF_HPP_INCLUDED
#define SGE_SPRITE_DETAIL_CONFIG_CONTAINS_IF_HPP_INCLUDED

#include <fcppt/config/external_begin.hpp>
#include <metal/list/any_of.hpp>
#include <metal/lambda/trait.hpp>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace sprite
{
namespace detail
{
namespace config
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
metal::any_of<
	Elements,
	metal::trait<
		Predicate
	>
>;

}
}
}
}

#endif
