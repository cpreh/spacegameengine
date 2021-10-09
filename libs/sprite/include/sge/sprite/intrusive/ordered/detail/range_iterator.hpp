//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_SPRITE_INTRUSIVE_ORDERED_DETAIL_RANGE_ITERATOR_HPP_INCLUDED
#define SGE_SPRITE_INTRUSIVE_ORDERED_DETAIL_RANGE_ITERATOR_HPP_INCLUDED

#include <sge/sprite/intrusive/ordered/detail/range_iterator_impl.hpp>

namespace sge::sprite::intrusive::ordered::detail
{

template <typename Choices, bool IsConst>
using range_iterator =
    typename sge::sprite::intrusive::ordered::detail::range_iterator_impl<Choices, IsConst>::type;

}

#endif
