//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_SPRITE_DETAIL_RENDER_UNSET_TEXTURE_STAGE_HPP_INCLUDED
#define SGE_SPRITE_DETAIL_RENDER_UNSET_TEXTURE_STAGE_HPP_INCLUDED

#include <sge/renderer/context/core.hpp> // IWYU pragma: keep
#include <sge/renderer/context/core_ref.hpp>
#include <sge/renderer/texture/const_optional_base_ref.hpp>
#include <sge/renderer/texture/stage.hpp>
#include <fcppt/tag_type.hpp>

namespace sge::sprite::detail::render
{

class unset_texture_stage
{
public:
  explicit unset_texture_stage(sge::renderer::context::core_ref const _render_context)
      : render_context_(_render_context)
  {
  }

  template <typename Level>
  void operator()(Level const &) const
  {
    this->render_context_.get().texture(
        sge::renderer::texture::const_optional_base_ref(),
        sge::renderer::texture::stage(fcppt::tag_type<Level>::value));
  }

private:
  sge::renderer::context::core_ref render_context_;
};

}

#endif
