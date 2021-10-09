//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_OPENGL_TEXTURE_FUNCS_SET_ACTIVE_LEVEL_HPP_INCLUDED
#define SGE_OPENGL_TEXTURE_FUNCS_SET_ACTIVE_LEVEL_HPP_INCLUDED

#include <sge/opengl/context/object_fwd.hpp>
#include <sge/renderer/texture/stage.hpp>
#include <fcppt/log/object_fwd.hpp>

namespace sge::opengl::texture::funcs
{

void set_active_level(
    fcppt::log::object &, // NOLINT(google-runtime-references)
    sge::opengl::context::object &, // NOLINT(google-runtime-references)
    sge::renderer::texture::stage);

}

#endif
