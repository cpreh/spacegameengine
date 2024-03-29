//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_SPRITE_GEOMETRY_DETAIL_FILL_POSITION_UNROTATED_HPP_INCLUDED
#define SGE_SPRITE_GEOMETRY_DETAIL_FILL_POSITION_UNROTATED_HPP_INCLUDED

#include <sge/renderer/vf/iterator_impl.hpp> // IWYU pragma: keep
#include <sge/renderer/vf/set_proxy.hpp>
#include <sge/renderer/vf/labels/pos.hpp>
#include <sge/sprite/object_impl.hpp>
#include <sge/sprite/detail/bounding_rect.hpp>
#include <sge/sprite/geometry/detail/float_rect.hpp>
#include <sge/sprite/geometry/detail/make_position.hpp>
#include <sge/sprite/types/basic/float_vector.hpp>
#include <fcppt/cast/static_cast_fun.hpp>
#include <fcppt/math/box/structure_cast.hpp>

namespace sge::sprite::geometry::detail
{

template <typename Iterator, typename Choices>
void fill_position_unrotated(Iterator _iterator, sge::sprite::object<Choices> const &_sprite)
{
  using type_choices = typename Choices::type_choices;

  using float_rect = sge::sprite::geometry::detail::float_rect<type_choices>;

  auto const rect(fcppt::math::box::structure_cast<float_rect, fcppt::cast::static_cast_fun>(
      sge::sprite::detail::bounding_rect(_sprite)));

  using float_vector = sge::sprite::types::basic::float_vector<type_choices>;

  sge::renderer::vf::set_proxy(
      *_iterator,
      sge::renderer::vf::labels::pos{},
      sge::sprite::geometry::detail::make_position<Choices>(
          float_vector(rect.left(), rect.top()), _sprite));

  ++_iterator;

  sge::renderer::vf::set_proxy(
      *_iterator,
      sge::renderer::vf::labels::pos{},
      sge::sprite::geometry::detail::make_position<Choices>(
          float_vector(rect.right(), rect.top()), _sprite));

  ++_iterator;

  sge::renderer::vf::set_proxy(
      *_iterator,
      sge::renderer::vf::labels::pos{},
      sge::sprite::geometry::detail::make_position<Choices>(
          float_vector(rect.right(), rect.bottom()), _sprite));

  ++_iterator;

  sge::renderer::vf::set_proxy(
      *_iterator,
      sge::renderer::vf::labels::pos{},
      sge::sprite::geometry::detail::make_position<Choices>(
          float_vector(rect.left(), rect.bottom()), _sprite));
}

}

#endif
