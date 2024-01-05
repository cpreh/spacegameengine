//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_SPRITE_GEOMETRY_DETAIL_INDEX_ARRAY_HPP_INCLUDED
#define SGE_SPRITE_GEOMETRY_DETAIL_INDEX_ARRAY_HPP_INCLUDED

#include <sge/sprite/geometry/detail/index_array_type.hpp>

namespace sge::sprite::geometry::detail
{

template <typename Choices>
struct index_array
{
  using array = sge::sprite::geometry::detail::index_array_type<Choices>;

  static array const value;
};

}

template <typename Choices>
typename sge::sprite::geometry::detail::index_array<Choices>::array const
    sge::sprite::geometry::detail::index_array<Choices>::value{0U, 1U, 2U, 0U, 2U, 3U};

#endif
