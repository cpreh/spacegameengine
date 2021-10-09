//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/opengl/common.hpp>
#include <sge/opengl/disable_client_state.hpp>
#include <sge/opengl/context/object_fwd.hpp>
#include <sge/opengl/texture/funcs/set_client_level.hpp>
#include <sge/opengl/vf/disable_texcoords.hpp>
#include <sge/renderer/texture/stage.hpp>
#include <fcppt/log/object_fwd.hpp>

void sge::opengl::vf::disable_texcoords(
    fcppt::log::object &_log,
    sge::opengl::context::object &_context,
    sge::renderer::texture::stage const _index)
{
  sge::opengl::texture::funcs::set_client_level(_log, _context, _index);

  sge::opengl::disable_client_state(GL_TEXTURE_COORD_ARRAY);
}
