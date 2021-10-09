//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_SPRITE_GEOMETRY_UPDATE_ONE_HPP_INCLUDED
#define SGE_SPRITE_GEOMETRY_UPDATE_ONE_HPP_INCLUDED

#include <sge/sprite/object_fwd.hpp>
#include <sge/sprite/compare/nothing.hpp>
#include <sge/sprite/geometry/make_single_range.hpp>
#include <sge/sprite/geometry/update.hpp>
#include <sge/sprite/render/range_impl.hpp>

namespace sge::sprite::geometry
{

template <typename Choices, typename Buffers>
inline sge::sprite::render::range<Choices>
update_one(sge::sprite::object<Choices> const &_sprite, Buffers &_buffers)
{
  return sge::sprite::geometry::update(
      sge::sprite::geometry::make_single_range(_sprite), sge::sprite::compare::nothing(), _buffers);
}

}

#endif
