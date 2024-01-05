//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_SPRITE_DETAIL_POS_FROM_CENTER_HPP_INCLUDED
#define SGE_SPRITE_DETAIL_POS_FROM_CENTER_HPP_INCLUDED

#include <sge/sprite/detail/get_size.hpp>
#include <sge/sprite/types/center.hpp>
#include <sge/sprite/types/vector.hpp>
#include <fcppt/literal.hpp>
#include <fcppt/math/dim/arithmetic.hpp> // IWYU pragma: keep
#include <fcppt/math/vector/dim.hpp> // IWYU pragma: keep

namespace sge::sprite::detail
{

template <typename Choices, typename Elements>
inline sge::sprite::types::vector<typename Choices::type_choices> pos_from_center(
    Elements const &_elements,
    sge::sprite::types::center<typename Choices::type_choices> const _center)
{
  return _center.get() - (sge::sprite::detail::get_size<Choices>(_elements) /
                          fcppt::literal<typename Choices::type_choices::unit_type>(2))
                             .get_unsafe();
}

}

#endif
