//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_SPRITE_DETAIL_PRIMITIVES_TEXTURE_POINT_SIZE_HPP_INCLUDED
#define SGE_SPRITE_DETAIL_PRIMITIVES_TEXTURE_POINT_SIZE_HPP_INCLUDED

#include <sge/sprite/config/custom_texture_point_size_fwd.hpp>
#include <sge/sprite/config/no_texture_point_size_fwd.hpp>
#include <sge/sprite/detail/transform_texture_levels_static.hpp>
#include <sge/sprite/roles/texture_point_size.hpp>
#include <sge/sprite/types/texture_point_size.hpp>
#include <fcppt/mpl/lambda.hpp>
#include <fcppt/mpl/list/object.hpp>
#include <fcppt/mpl/list/size.hpp>
#include <fcppt/record/element.hpp>

namespace sge::sprite::detail::primitives
{

template <typename Choices, typename Levels, typename PointSize>
struct texture_point_size;

template <typename Choices, typename Levels>
struct texture_point_size<Choices, Levels, sge::sprite::config::no_texture_point_size>
{
  using type = fcppt::mpl::list::object<>;
};

template <typename Choices, typename Levels, typename AttributeNames>
struct texture_point_size<
    Choices,
    Levels,
    sge::sprite::config::custom_texture_point_size<AttributeNames>>
{
private:
  template <typename Level>
  using make_role = fcppt::record::element<
      sge::sprite::roles::texture_point_size<Level::value>,
      sge::sprite::types::texture_point_size<typename Choices::type_choices>>;

  static_assert(
      fcppt::mpl::list::size<AttributeNames>::value == Levels::value,
      "The number of attribute names must match the number of texture levels");

public:
  using type =
      sge::sprite::detail::transform_texture_levels_static<fcppt::mpl::lambda<make_role>, Levels>;
};

}

#endif
