//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_SPRITE_DETAIL_CONFIG_CONTAINS_IF_HPP_INCLUDED
#define SGE_SPRITE_DETAIL_CONFIG_CONTAINS_IF_HPP_INCLUDED

#include <fcppt/config/external_begin.hpp>
#include <brigand/algorithms/find.hpp>
#include <brigand/functions/lambda/bind.hpp>
#include <brigand/types/args.hpp>
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
brigand::found<
	Elements,
	brigand::bind<
		Predicate,
		brigand::_1
	>
>;

}
}
}
}

#endif
