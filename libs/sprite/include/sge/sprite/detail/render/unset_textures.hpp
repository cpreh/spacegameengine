//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_SPRITE_DETAIL_RENDER_UNSET_TEXTURES_HPP_INCLUDED
#define SGE_SPRITE_DETAIL_RENDER_UNSET_TEXTURES_HPP_INCLUDED

#include <sge/renderer/context/core_fwd.hpp>
#include <sge/sprite/detail/config/has_texture_levels.hpp>
#include <sge/sprite/detail/config/texture_levels.hpp>
#include <sge/sprite/detail/render/unset_texture_stages.hpp>
#include <fcppt/not.hpp>

namespace sge::sprite::detail::render
{

template <typename Choices>
void unset_textures(
    sge::renderer::context::core &_render_context // NOLINT(google-runtime-references)
    )
  requires(sge::sprite::detail::config::has_texture_levels<Choices>::value)
{
  sge::sprite::detail::render::unset_texture_stages<
      sge::sprite::detail::config::texture_levels<Choices>>(_render_context);
}

template <typename Choices>
inline void unset_textures(sge::renderer::context::core &) // NOLINT(google-runtime-references)
  requires(fcppt::not_(sge::sprite::detail::config::has_texture_levels<Choices>::value))
{
}
}

#endif
