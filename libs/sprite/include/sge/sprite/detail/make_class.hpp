//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_SPRITE_DETAIL_MAKE_CLASS_HPP_INCLUDED
#define SGE_SPRITE_DETAIL_MAKE_CLASS_HPP_INCLUDED

#include <sge/sprite/detail/apply_choices.hpp>
#include <fcppt/mpl/list/append.hpp>
#include <fcppt/mpl/list/join.hpp>
#include <fcppt/mpl/list/object.hpp>
#include <fcppt/record/from_list.hpp>


namespace sge::sprite::detail
{

template<
	typename Choices
>
using make_class
=
fcppt::record::from_list<
	fcppt::mpl::list::join<
		typename
		sge::sprite::detail::apply_choices<
			Choices,
			fcppt::mpl::list::append<
				typename
				Choices::optional_elements,
				fcppt::mpl::list::object<
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

#endif
