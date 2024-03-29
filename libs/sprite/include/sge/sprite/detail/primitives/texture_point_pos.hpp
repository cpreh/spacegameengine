//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_SPRITE_DETAIL_PRIMITIVES_TEXTURE_POINT_POS_HPP_INCLUDED
#define SGE_SPRITE_DETAIL_PRIMITIVES_TEXTURE_POINT_POS_HPP_INCLUDED

#include <sge/sprite/config/custom_texture_point_pos_fwd.hpp>
#include <sge/sprite/detail/transform_texture_levels_static.hpp>
#include <sge/sprite/roles/texture_point_pos.hpp>
#include <sge/sprite/types/texture_point_pos.hpp>
#include <fcppt/mpl/lambda.hpp>
#include <fcppt/mpl/list/object.hpp>
#include <fcppt/record/element.hpp>

namespace sge::sprite::detail::primitives
{

// TODO(philipp): Add a test for this or remove.
template <typename Choices, typename Levels, typename PointPos>
struct texture_point_pos;

template <typename Choices, typename Levels>
struct texture_point_pos<Choices, Levels, sge::sprite::config::custom_texture_point_pos<false>>
{
  using type = fcppt::mpl::list::object<>;
};

template <typename Choices, typename Levels>
struct texture_point_pos<Choices, Levels, sge::sprite::config::custom_texture_point_pos<true>>
{
private:
  template <typename Level>
  using make_role = fcppt::record::element<
      sge::sprite::roles::texture_point_pos<Level::value>,
      sge::sprite::types::texture_point_pos<typename Choices::type_choices>>;

public:
  using type =
      sge::sprite::detail::transform_texture_levels_static<fcppt::mpl::lambda<make_role>, Levels>;
};

}

#endif
