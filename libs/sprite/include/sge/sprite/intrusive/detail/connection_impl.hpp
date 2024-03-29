//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_SPRITE_INTRUSIVE_DETAIL_CONNECTION_IMPL_HPP_INCLUDED
#define SGE_SPRITE_INTRUSIVE_DETAIL_CONNECTION_IMPL_HPP_INCLUDED

#include <sge/sprite/count.hpp> // IWYU pragma: keep
#include <sge/sprite/object_decl.hpp> // IWYU pragma: keep
#include <sge/sprite/intrusive/detail/connection_decl.hpp> // IWYU pragma: export
#include <fcppt/reference_impl.hpp> // IWYU pragma: keep
#include <fcppt/strong_typedef_arithmetic.hpp>

template <typename Choices>
sge::sprite::intrusive::detail::connection<Choices>::connection(
    list_ref const _list, count_ref const _count)
    : base(), list_(_list), count_(_count)
{
}

namespace sge::sprite::intrusive::detail
{
template <typename Choices>
connection<Choices>::~connection() = default;
}

template <typename Choices>
void sge::sprite::intrusive::detail::connection<Choices>::add(object &_sprite)
{
  list_.get().push_back(_sprite);

  ++count_.get();
}

template <typename Choices>
void sge::sprite::intrusive::detail::connection<Choices>::remove()
{
  --count_.get();
}

#endif
