//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_SPRITE_DETAIL_RENDER_SET_TEXTURES_HPP_INCLUDED
#define SGE_SPRITE_DETAIL_RENDER_SET_TEXTURES_HPP_INCLUDED

#include <sge/renderer/context/core.hpp>
#include <sge/renderer/texture/base.hpp>
#include <sge/renderer/texture/const_optional_base_ref.hpp>
#include <sge/renderer/texture/planar.hpp>
#include <sge/renderer/texture/stage.hpp>
#include <sge/sprite/detail/apply_texture_levels.hpp>
#include <sge/sprite/detail/config/has_texture_levels.hpp>
#include <sge/sprite/detail/config/texture_levels.hpp>
#include <sge/sprite/render/range_part_impl.hpp>
#include <fcppt/not.hpp>
#include <fcppt/reference_to_base.hpp>
#include <fcppt/tag_type.hpp>
#include <fcppt/use.hpp>
#include <fcppt/config/external_begin.hpp>
#include <type_traits>
#include <fcppt/config/external_end.hpp>

namespace sge::sprite::detail::render
{

template <typename Choices>
std::enable_if_t<
    sge::sprite::detail::config::has_texture_levels<Choices>::value,
    void>
set_textures(
    sge::renderer::context::core &_render_context, // NOLINT(google-runtime-references)
    sge::sprite::render::range_part<Choices> const &_range)
{
  sge::sprite::detail::apply_texture_levels<sge::sprite::detail::config::texture_levels<Choices>>(
      [&_render_context, &_range](auto const &_level)
      {
        FCPPT_USE(_level);

        using cur_level = fcppt::tag_type<decltype(_level)>;

        _render_context.texture(
            sge::renderer::texture::const_optional_base_ref{
                fcppt::reference_to_base<sge::renderer::texture::base const>(
                    _range.template texture_level<cur_level::value>())},
            sge::renderer::texture::stage(cur_level::value));
      });
}

template <typename Choices>
std::enable_if_t<
    fcppt::not_(sge::sprite::detail::config::has_texture_levels<Choices>::value),
    void>
set_textures(
    sge::renderer::context::core &, // NOLINT(google-runtime-references)
    sge::sprite::render::range_part<Choices> const &)
{
}

}

#endif
