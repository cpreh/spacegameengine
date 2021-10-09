//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/opengl/context/base.hpp>
#include <sge/opengl/context/id.hpp>
#include <sge/opengl/context/make_id.hpp>
#include <sge/opengl/texture/base_fwd.hpp>
#include <sge/opengl/texture/bind_context.hpp>
#include <sge/opengl/texture/const_optional_base_ref.hpp>
#include <sge/renderer/texture/stage.hpp>
#include <fcppt/container/index_map_impl.hpp>
#include <fcppt/preprocessor/disable_clang_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>

sge::opengl::texture::bind_context::bind_context() : sge::opengl::context::base(), map_() {}

sge::opengl::texture::bind_context::~bind_context() = default;

sge::opengl::texture::const_optional_base_ref
sge::opengl::texture::bind_context::stage(sge::renderer::texture::stage const _stage) const
{
  return map_[_stage.get()];
}

void sge::opengl::texture::bind_context::stage(
    sge::renderer::texture::stage const _stage,
    sge::opengl::texture::const_optional_base_ref const &_texture)
{
  map_[_stage.get()] = _texture;
}

FCPPT_PP_PUSH_WARNING
FCPPT_PP_DISABLE_CLANG_WARNING(-Wglobal-constructors)

sge::opengl::context::id const
    sge::opengl::texture::bind_context::static_id(sge::opengl::context::make_id());

FCPPT_PP_POP_WARNING
