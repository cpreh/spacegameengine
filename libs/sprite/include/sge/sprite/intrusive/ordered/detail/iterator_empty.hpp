//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_SPRITE_INTRUSIVE_ORDERED_DETAIL_ITERATOR_EMPTY_HPP_INCLUDED
#define SGE_SPRITE_INTRUSIVE_ORDERED_DETAIL_ITERATOR_EMPTY_HPP_INCLUDED

namespace sge::sprite::intrusive::ordered::detail
{

struct iterator_empty
{
  template <typename T>
  bool operator()(T const &_ref) const
  {
    return !_ref.second->range().empty();
  }
};

}

#endif
