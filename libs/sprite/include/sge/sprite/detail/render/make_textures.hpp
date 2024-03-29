//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_SPRITE_DETAIL_RENDER_MAKE_TEXTURES_HPP_INCLUDED
#define SGE_SPRITE_DETAIL_RENDER_MAKE_TEXTURES_HPP_INCLUDED

#include <sge/sprite/detail/transform_texture_levels_static.hpp>
#include <sge/sprite/detail/config/has_texture_levels.hpp>
#include <sge/sprite/detail/config/texture_levels.hpp>
#include <sge/sprite/detail/roles/texture.hpp>
#include <sge/sprite/render/texture_ref.hpp>
#include <fcppt/not.hpp>
#include <fcppt/mpl/lambda.hpp>
#include <fcppt/mpl/list/object.hpp>
#include <fcppt/record/element.hpp>
#include <fcppt/config/external_begin.hpp>
#include <type_traits>
#include <fcppt/config/external_end.hpp>

namespace sge::sprite::detail::render
{

template <typename Choices, typename Enable = void>
struct make_textures;

template <typename Choices>
struct make_textures<
    Choices,
    std::enable_if_t<sge::sprite::detail::config::has_texture_levels<Choices>::value>>
{
private:
  template <typename Level>
  using make_texture_role = fcppt::record::
      element<sge::sprite::detail::roles::texture<Level::value>, sge::sprite::render::texture_ref>;

public:
  using type = sge::sprite::detail::transform_texture_levels_static<
      fcppt::mpl::lambda<make_texture_role>,
      sge::sprite::detail::config::texture_levels<Choices>>;
};

template <typename Choices>
struct make_textures<
    Choices,
    std::enable_if_t<fcppt::not_(sge::sprite::detail::config::has_texture_levels<Choices>::value)>>
{
  using type = fcppt::mpl::list::object<>;
};

}

#endif
