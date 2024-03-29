//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_SPRITE_INTRUSIVE_ORDERED_DETAIL_RANGE_ITERATOR_IMPL_HPP_INCLUDED
#define SGE_SPRITE_INTRUSIVE_ORDERED_DETAIL_RANGE_ITERATOR_IMPL_HPP_INCLUDED

#include <sge/sprite/intrusive/collection_decl.hpp>
#include <fcppt/config/external_begin.hpp>
#include <type_traits>
#include <fcppt/config/external_end.hpp>

namespace sge::sprite::intrusive::ordered::detail
{

template <typename Choices, bool IsConst>
struct range_iterator_impl
{
  using collection_type = sge::sprite::intrusive::collection<Choices>;

  using type = std::conditional_t<
      IsConst,
      typename collection_type::const_range_type::iterator,
      typename collection_type::range_type::iterator>;
};

}

#endif
