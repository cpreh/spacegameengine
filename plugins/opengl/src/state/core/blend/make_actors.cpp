//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/opengl/call.hpp>
#include <sge/opengl/context/object_ref.hpp>
#include <sge/opengl/convert/to_gl_bool.hpp>
#include <sge/opengl/state/actor.hpp>
#include <sge/opengl/state/actor_vector.hpp>
#include <sge/opengl/state/wrap_error_handler.hpp>
#include <sge/opengl/state/core/blend/alpha.hpp>
#include <sge/opengl/state/core/blend/make_actors.hpp>
#include <sge/renderer/opengl/glinclude.hpp>
#include <sge/renderer/state/core/blend/parameters.hpp>
#include <fcppt/text.hpp>
#include <fcppt/container/join.hpp>

sge::opengl::state::actor_vector sge::opengl::state::core::blend::make_actors(
    sge::opengl::context::object_ref const _context,
    sge::renderer::state::core::blend::parameters const &_parameters)
{
  return fcppt::container::join(
      sge::opengl::state::core::blend::alpha(_context, _parameters.alpha_variant()),
      sge::opengl::state::actor_vector{
          sge::opengl::state::wrap_error_handler<sge::opengl::state::actor>(
              [write_mask = _parameters.write_mask()]
              {
                sge::opengl::call(
                    ::glColorMask,
                    sge::opengl::convert::to_gl_bool(write_mask.write_red().get()),
                    sge::opengl::convert::to_gl_bool(write_mask.write_green().get()),
                    sge::opengl::convert::to_gl_bool(write_mask.write_blue().get()),
                    sge::opengl::convert::to_gl_bool(write_mask.write_alpha().get()));
              },
              FCPPT_TEXT("glColorMask"))});
}
