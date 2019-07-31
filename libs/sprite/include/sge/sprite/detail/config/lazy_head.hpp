//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_SPRITE_DETAIL_CONFIG_LAZY_HEAD_HPP_INCLUDED
#define SGE_SPRITE_DETAIL_CONFIG_LAZY_HEAD_HPP_INCLUDED

#include <fcppt/config/external_begin.hpp>
#include <brigand/sequences/front.hpp>
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
	template<
		typename
	> class Function,
	typename List
>
struct lazy_head
{
	typedef
	Function<
		brigand::front<
			List
		>
	>
	type;
};

}
}
}
}

#endif
