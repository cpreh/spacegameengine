//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_SPRITE_INTRUSIVE_ORDERED_DETAIL_ITERATOR_BASE_HPP_INCLUDED
#define SGE_SPRITE_INTRUSIVE_ORDERED_DETAIL_ITERATOR_BASE_HPP_INCLUDED

#include <sge/sprite/intrusive/ordered/detail/iterator_base_impl.hpp>


namespace sge
{
namespace sprite
{
namespace intrusive
{
namespace ordered
{
namespace detail
{

template<
	typename Choices,
	typename Order,
	bool IsConst
>
using
iterator_base
=
typename
sge::sprite::intrusive::ordered::detail::iterator_base_impl<
	Choices,
	Order,
	IsConst
>::type;

}
}
}
}
}

#endif
