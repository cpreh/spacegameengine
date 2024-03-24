//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_SPRITE_GEOMETRY_DETAIL_FILL_TEXTURE_LEVELS_HPP_INCLUDED
#define SGE_SPRITE_GEOMETRY_DETAIL_FILL_TEXTURE_LEVELS_HPP_INCLUDED

#include <sge/sprite/object_impl.hpp>
#include <sge/sprite/config/is_normal_size.hpp>
#include <sge/sprite/detail/apply_texture_levels.hpp>
#include <sge/sprite/detail/config/has_texture.hpp>
#include <sge/sprite/detail/config/has_texture_levels.hpp>
#include <sge/sprite/detail/config/texture_levels.hpp>
#include <sge/sprite/geometry/detail/fill_texture_level.hpp>
#include <fcppt/not.hpp>
#include <fcppt/type_traits/implication.hpp>

namespace sge::sprite::geometry::detail
{

template <typename Iterator, typename Choices>
inline void
fill_texture_levels(Iterator const &_iterator, sge::sprite::object<Choices> const &_sprite)
requires(sge::sprite::detail::config::has_texture_levels<Choices>::value)
{
  static_assert(
      fcppt::type_traits::implication<
          sge::sprite::detail::config::has_texture<Choices>,
          sge::sprite::config::is_normal_size<typename Choices::size_choice>>::value,
      "Normal textures require normal sizes");

  sge::sprite::detail::apply_texture_levels<sge::sprite::detail::config::texture_levels<Choices>>(
      sge::sprite::geometry::detail::fill_texture_level<Iterator, Choices>(_iterator, _sprite));
}

template <typename Iterator, typename Choices>
inline void fill_texture_levels(Iterator const &, sge::sprite::object<Choices> const &)
  requires(fcppt::not_(sge::sprite::detail::config::has_texture_levels<Choices>::value))
{
}

}

#endif
