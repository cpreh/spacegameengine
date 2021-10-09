//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_SPRITE_INTRUSIVE_ORDERED_RANGE_IMPL_HPP_INCLUDED
#define SGE_SPRITE_INTRUSIVE_ORDERED_RANGE_IMPL_HPP_INCLUDED

#include <sge/sprite/count.hpp>
#include <sge/sprite/intrusive/ordered/iterator_impl.hpp>
#include <sge/sprite/intrusive/ordered/range_decl.hpp>
#include <sge/sprite/intrusive/ordered/detail/range_size.hpp>

template <typename Choices, typename Order, bool IsConst>
sge::sprite::intrusive::ordered::range<Choices, Order, IsConst>::range(
    ordered_map_reference const _ordered_map)
    : ordered_map_(_ordered_map),
      size_(sge::sprite::intrusive::ordered::detail::range_size<Order, Choices>(_ordered_map.get()))
{
}

template <typename Choices, typename Order, bool IsConst>
typename sge::sprite::intrusive::ordered::range<Choices, Order, IsConst>::iterator
sge::sprite::intrusive::ordered::range<Choices, Order, IsConst>::begin() const
{
  return iterator(ordered_map_.get().begin(), ordered_map_.get().end());
}

template <typename Choices, typename Order, bool IsConst>
typename sge::sprite::intrusive::ordered::range<Choices, Order, IsConst>::iterator
sge::sprite::intrusive::ordered::range<Choices, Order, IsConst>::end() const
{
  return iterator(ordered_map_.get().end(), ordered_map_.get().end());
}

template <typename Choices, typename Order, bool IsConst>
sge::sprite::count sge::sprite::intrusive::ordered::range<Choices, Order, IsConst>::size() const
{
  return size_;
}

template <typename Choices, typename Order, bool IsConst>
bool sge::sprite::intrusive::ordered::range<Choices, Order, IsConst>::empty() const
{
  return size_.get() == 0U;
}

template <typename Choices, typename Order, bool IsConst>
template <typename Equal>
void sge::sprite::intrusive::ordered::range<Choices, Order, IsConst>::sort(Equal const &_func) const
{
  for (auto const &element : ordered_map_.get())
  {
    element.second->range().sort(_func);
  }
}

#endif
