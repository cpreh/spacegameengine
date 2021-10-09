//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_SPRITE_COMPARE_DETAIL_TEXTURES_HPP_INCLUDED
#define SGE_SPRITE_COMPARE_DETAIL_TEXTURES_HPP_INCLUDED

#include <sge/sprite/object_fwd.hpp>
#include <sge/sprite/texture_level.hpp>
#include <sge/sprite/compare/texture_level_equal.hpp>
#include <sge/sprite/compare/texture_level_less.hpp>
#include <sge/sprite/config/texture_level_count.hpp>

namespace sge::sprite::compare::detail
{

template <sge::sprite::texture_level Level>
struct textures
{
  template <typename Choices>
  static bool
  execute(sge::sprite::object<Choices> const &_left, sge::sprite::object<Choices> const &_right)
  {
    using current_level = sge::sprite::config::texture_level_count<Level - 1U>;

    return !sge::sprite::compare::texture_level_equal<current_level>(_left, _right)
               ? sge::sprite::compare::texture_level_less<current_level>(_left, _right)
               : sge::sprite::compare::detail::textures<Level - 1U>::execute(_left, _right);
  }
};

template <>
struct textures<0U>
{
  template <typename Choices>
  static bool execute(sge::sprite::object<Choices> const &, sge::sprite::object<Choices> const &)
  {
    return false;
  }
};

}

#endif
