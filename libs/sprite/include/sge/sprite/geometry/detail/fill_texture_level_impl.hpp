//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_SPRITE_GEOMETRY_DETAIL_FILL_TEXTURE_LEVEL_IMPL_HPP_INCLUDED
#define SGE_SPRITE_GEOMETRY_DETAIL_FILL_TEXTURE_LEVEL_IMPL_HPP_INCLUDED

#include <sge/sprite/object_impl.hpp>
#include <sge/sprite/detail/config/has_texture.hpp>
#include <sge/sprite/detail/config/has_texture_point_size.hpp>
#include <sge/sprite/geometry/detail/fill_texture_coordinates.hpp>
#include <sge/sprite/geometry/detail/fill_texture_point.hpp>
#include <sge/texture/part_fwd.hpp>

namespace sge::sprite::geometry::detail
{

template <typename Level, typename Iterator, typename Choices>
inline void fill_texture_level_impl(
    Level const &_level,
    Iterator const _iterator,
    sge::sprite::object<Choices> const &_sprite,
    sge::texture::part const &_texture)
  requires(sge::sprite::detail::config::has_texture<Choices>::value)
{
  sge::sprite::geometry::detail::fill_texture_coordinates(_level, _iterator, _sprite, _texture);
}

template <typename Level, typename Iterator, typename Choices>
inline void fill_texture_level_impl(
    Level const &_level,
    Iterator const _iterator,
    sge::sprite::object<Choices> const &_sprite,
    sge::texture::part const &)
  requires(sge::sprite::detail::config::has_texture_point_size<Choices>::value)
{
  sge::sprite::geometry::detail::fill_texture_point(_level, _iterator, _sprite);
}

}

#endif
