//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_SPRITE_DETAIL_APPLY_CHOICES_HPP_INCLUDED
#define SGE_SPRITE_DETAIL_APPLY_CHOICES_HPP_INCLUDED

#include <fcppt/config/external_begin.hpp>
#include <metal.hpp>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace sprite
{
namespace detail
{

template<
	typename Choices,
	typename Functions
>
struct apply_choices;

// TODO: Can we do this in a better way?
template<
	typename Choices,
	typename... Functions
>
struct apply_choices<
	Choices,
	metal::list<
		Functions...
	>
>
{
	typedef
	metal::list<
		typename
		Functions :: template apply<
			Choices
		>::type ...
	>
	type;
};

}
}
}

#endif
