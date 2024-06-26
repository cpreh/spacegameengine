//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_SPRITE_COMPARE_DEFAULT_HPP_INCLUDED
#define SGE_SPRITE_COMPARE_DEFAULT_HPP_INCLUDED

#include <sge/sprite/object_fwd.hpp>
#include <sge/sprite/compare/nothing.hpp>
#include <sge/sprite/compare/textures.hpp>
#include <sge/sprite/detail/config/has_texture.hpp>
#include <fcppt/not.hpp>
#include <fcppt/config/external_begin.hpp>
#include <type_traits>
#include <fcppt/config/external_end.hpp>

namespace sge::sprite::compare
{

struct default_
{
  template <typename Choices>
  using is_trivial = std::negation<sge::sprite::detail::config::has_texture<Choices>>;

  template <typename Choices>
  bool operator()(
      sge::sprite::object<Choices> const &_left, sge::sprite::object<Choices> const &_right) const
    requires(sge::sprite::detail::config::has_texture<Choices>::value)
  {
    return sge::sprite::compare::textures()(_left, _right);
  }

  template <typename Choices>
  bool operator()(
      sge::sprite::object<Choices> const &_left, sge::sprite::object<Choices> const &_right) const
    requires(fcppt::not_(sge::sprite::detail::config::has_texture<Choices>::value))
  {
    return sge::sprite::compare::nothing()(_left, _right);
  }
};

}

#endif
