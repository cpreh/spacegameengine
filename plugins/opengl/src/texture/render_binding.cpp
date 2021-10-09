//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/opengl/texture/active_level.hpp>
#include <sge/opengl/texture/binding.hpp>
#include <sge/opengl/texture/render_binding.hpp>
#include <sge/opengl/texture/type.hpp>
#include <sge/renderer/texture/stage.hpp>

sge::opengl::texture::render_binding::render_binding(
    sge::opengl::texture::active_level const &_active_level, sge::opengl::texture::type const _type)
    : sge::opengl::texture::binding(), stage_(_active_level.stage()), type_(_type)
{
}

sge::opengl::texture::render_binding::~render_binding() = default;

sge::renderer::texture::stage sge::opengl::texture::render_binding::stage() const { return stage_; }

sge::opengl::texture::type sge::opengl::texture::render_binding::type() const { return type_; }
