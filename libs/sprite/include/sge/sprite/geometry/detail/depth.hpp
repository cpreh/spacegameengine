//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_SPRITE_GEOMETRY_DETAIL_DEPTH_HPP_INCLUDED
#define SGE_SPRITE_GEOMETRY_DETAIL_DEPTH_HPP_INCLUDED

#include <sge/sprite/object_impl.hpp>
#include <sge/sprite/detail/config/has_depth.hpp>
#include <fcppt/literal.hpp>
#include <fcppt/not.hpp>

namespace sge::sprite::geometry::detail
{

template <typename Choices>
inline typename Choices::type_choices::float_type depth(sge::sprite::object<Choices> const &_sprite)
  requires(sge::sprite::detail::config::has_depth<Choices>::value)
{
  return _sprite.z();
}

template <typename Choices>
inline typename Choices::type_choices::float_type depth(sge::sprite::object<Choices> const &)
  requires(fcppt::not_(sge::sprite::detail::config::has_depth<Choices>::value))
{
  return fcppt::literal<typename Choices::type_choices::float_type>(0);
}
}

#endif
