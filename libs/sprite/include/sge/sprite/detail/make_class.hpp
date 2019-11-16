//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_SPRITE_DETAIL_MAKE_CLASS_HPP_INCLUDED
#define SGE_SPRITE_DETAIL_MAKE_CLASS_HPP_INCLUDED

#include <sge/sprite/detail/apply_choices.hpp>
#include <fcppt/record/object_impl.hpp>
#include <fcppt/config/external_begin.hpp>
#include <metal/list/flatten.hpp>
#include <metal/list/join.hpp>
#include <metal/list/list.hpp>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace sprite
{
namespace detail
{

template<
	typename Choices
>
using make_class
=
fcppt::record::object<
	metal::flatten<
		typename
		sge::sprite::detail::apply_choices<
			Choices,
			metal::join<
				typename
				Choices::optional_elements,
				metal::list<
					typename
					Choices::pos_choice,
					typename
					Choices::size_choice
				>
			>
		>::type
	>
>;

}
}
}

#endif
