//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_SPRITE_DETAIL_CONFIG_FIND_IF_IMPL_HPP_INCLUDED
#define SGE_SPRITE_DETAIL_CONFIG_FIND_IF_IMPL_HPP_INCLUDED

#include <fcppt/config/external_begin.hpp>
#include <metal.hpp>
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
struct find_if_impl
{
	typedef
	metal::copy_if<
		Elements,
		metal::trait<
			Predicate
		>
	>
	type;

	// TODO
/*
	static_assert(
		metal::size<
			type
		>::value
		<=
		1u,
		"Option specified multiple times"
	);*/
};

}
}
}
}

#endif
