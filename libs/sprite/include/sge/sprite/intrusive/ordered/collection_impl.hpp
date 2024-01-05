//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_SPRITE_INTRUSIVE_ORDERED_COLLECTION_IMPL_HPP_INCLUDED
#define SGE_SPRITE_INTRUSIVE_ORDERED_COLLECTION_IMPL_HPP_INCLUDED

#include <sge/sprite/intrusive/collection_impl.hpp>
#include <sge/sprite/intrusive/connection_ref.hpp> // IWYU pragma: keep
#include <sge/sprite/intrusive/ordered/collection_decl.hpp> // IWYU pragma: export
#include <sge/sprite/intrusive/ordered/range_impl.hpp> // IWYU pragma: keep
#include <fcppt/make_ref.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/container/get_or_insert.hpp>

template <typename Choices, typename Order>
sge::sprite::intrusive::ordered::collection<Choices, Order>::collection() : collections_()
{
}

namespace sge::sprite::intrusive::ordered
{
template <typename Choices, typename Order>
collection<Choices, Order>::~collection() = default;
}

template <typename Choices, typename Order>
typename sge::sprite::intrusive::ordered::collection<Choices, Order>::collection_base &
sge::sprite::intrusive::ordered::collection<Choices, Order>::get(order const &_order)
{
  return *fcppt::container::get_or_insert(
      collections_,
      _order,
      [](Order) { return fcppt::make_unique_ptr<sge::sprite::intrusive::collection<Choices>>(); });
}

template <typename Choices, typename Order>
typename sge::sprite::intrusive::ordered::collection<Choices, Order>::connection_ref
sge::sprite::intrusive::ordered::collection<Choices, Order>::connection(order const &_order)
{
  return this->get(_order).connection();
}
template <typename Choices, typename Order>
typename sge::sprite::intrusive::ordered::collection<Choices, Order>::range_type
sge::sprite::intrusive::ordered::collection<Choices, Order>::range()
{
  return range_type(fcppt::make_ref(collections_));
}

template <typename Choices, typename Order>
typename sge::sprite::intrusive::ordered::collection<Choices, Order>::const_range_type
sge::sprite::intrusive::ordered::collection<Choices, Order>::range() const
{
  return const_range_type(fcppt::make_ref(collections_));
}

template <typename Choices, typename Order>
template <typename Function>
void sge::sprite::intrusive::ordered::collection<Choices, Order>::for_each(
    Function const &_function)
{
  for (auto const &element : collections_)
  {
    _function(element.second->range());
  }
}

#endif
