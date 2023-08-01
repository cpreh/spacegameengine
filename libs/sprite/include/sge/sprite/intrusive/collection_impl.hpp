//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_SPRITE_INTRUSIVE_COLLECTION_IMPL_HPP_INCLUDED
#define SGE_SPRITE_INTRUSIVE_COLLECTION_IMPL_HPP_INCLUDED

#include <sge/sprite/object_impl.hpp>
#include <sge/sprite/intrusive/collection_decl.hpp>
#include <sge/sprite/intrusive/connection_fwd.hpp>
#include <sge/sprite/intrusive/connection_ref.hpp>
#include <sge/sprite/intrusive/range_impl.hpp>
#include <sge/sprite/intrusive/detail/connection_impl.hpp>
#include <fcppt/make_cref.hpp>
#include <fcppt/make_ref.hpp>
#include <fcppt/reference_to_base.hpp>

template <typename Choices>
sge::sprite::intrusive::collection<Choices>::collection()
    : sprites_(), count_(0U), connection_(fcppt::make_ref(sprites_), fcppt::make_ref(count_))
{
}

namespace sge::sprite::intrusive
{
template <typename Choices>
collection<Choices>::~collection() = default;
}

template <typename Choices>
typename sge::sprite::intrusive::collection<Choices>::connection_ref
sge::sprite::intrusive::collection<Choices>::connection()
{
  return fcppt::reference_to_base<sge::sprite::intrusive::connection<Choices>>(
      fcppt::make_ref(this->connection_));
}

template <typename Choices>
typename sge::sprite::intrusive::collection<Choices>::range_type
sge::sprite::intrusive::collection<Choices>::range()
{
  return range_type(fcppt::make_ref(sprites_), count_);
}

template <typename Choices>
typename sge::sprite::intrusive::collection<Choices>::const_range_type
sge::sprite::intrusive::collection<Choices>::range() const
{
  return const_range_type(fcppt::make_cref(sprites_), count_);
}

#endif
