//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_SPRITE_GEOMETRY_DETAIL_FILL_TEXTURE_POINT_HPP_INCLUDED
#define SGE_SPRITE_GEOMETRY_DETAIL_FILL_TEXTURE_POINT_HPP_INCLUDED

#include <sge/sprite/object_impl.hpp>
#include <sge/sprite/detail/config/has_texture_point_size.hpp>
#include <sge/sprite/geometry/detail/fill_texture_point_pos.hpp>
#include <sge/sprite/geometry/detail/fill_texture_point_size.hpp>
#include <fcppt/not.hpp>

namespace sge::sprite::geometry::detail
{

template <typename Level, typename Iterator, typename Choices>
inline void fill_texture_point(
    Level const &_level, Iterator const _iterator, sge::sprite::object<Choices> const &_sprite)
  requires(sge::sprite::detail::config::has_texture_point_size<Choices>::value)
{
  sge::sprite::geometry::detail::fill_texture_point_pos(_level, _iterator, _sprite);

  sge::sprite::geometry::detail::fill_texture_point_size(_level, _iterator, _sprite);
}

template <typename Level, typename Iterator, typename Choices>
inline void fill_texture_point(Level const &, Iterator, sge::sprite::object<Choices> const &)
  requires(fcppt::not_(sge::sprite::detail::config::has_texture_point_size<Choices>::value))
{
}

}

#endif
