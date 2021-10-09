//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_SPRITE_DETAIL_CONFIG_FIND_IF_IMPL_HPP_INCLUDED
#define SGE_SPRITE_DETAIL_CONFIG_FIND_IF_IMPL_HPP_INCLUDED

#include <fcppt/mpl/lambda.hpp>
#include <fcppt/mpl/list/keep_if.hpp>

namespace sge::sprite::detail::config
{

template <typename Elements, template <typename> class Predicate>
struct find_if_impl
{
  using type = fcppt::mpl::list::keep_if<Elements, fcppt::mpl::lambda<Predicate>>;

  // TODO(philipp)
  /*
	static_assert(
		fcppt::mpl::list::size<
			type
		>::value
		<=
		1u,
		"Option specified multiple times"
	);*/
};

}

#endif
