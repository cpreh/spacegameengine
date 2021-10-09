//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_SPRITE_GEOMETRY_DETAIL_MAKE_POSITION_HPP_INCLUDED
#define SGE_SPRITE_GEOMETRY_DETAIL_MAKE_POSITION_HPP_INCLUDED

#include <sge/sprite/object_fwd.hpp>
#include <sge/sprite/geometry/detail/depth.hpp>
#include <sge/sprite/geometry/detail/pos_packed_type.hpp>
#include <fcppt/math/vector/push_back.hpp>

namespace sge::sprite::geometry::detail
{

template <typename Choices, typename Point>
inline sge::sprite::geometry::detail::pos_packed_type<Choices>
make_position(Point const &_point, sge::sprite::object<Choices> const &_sprite)
{
  return fcppt::math::vector::push_back(_point, sge::sprite::geometry::detail::depth(_sprite));
}

}

#endif
