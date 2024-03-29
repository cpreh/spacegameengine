//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/opengl/context/base.hpp>
#include <sge/opengl/context/id.hpp>
#include <sge/opengl/context/make_id.hpp>
#include <sge/opengl/texture/surface_config.hpp>
#include <sge/opengl/texture/surface_context.hpp>
#include <fcppt/preprocessor/disable_clang_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>

sge::opengl::texture::surface_context::surface_context() : sge::opengl::context::base(), config_{}
{
}

sge::opengl::texture::surface_context::~surface_context() = default;

sge::opengl::texture::surface_config const &sge::opengl::texture::surface_context::config() const
{
  return config_;
}

FCPPT_PP_PUSH_WARNING
FCPPT_PP_DISABLE_CLANG_WARNING(-Wglobal-constructors)

sge::opengl::context::id const
    sge::opengl::texture::surface_context::static_id(sge::opengl::context::make_id());

FCPPT_PP_POP_WARNING
