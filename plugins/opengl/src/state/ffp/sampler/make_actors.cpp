//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/opengl/ext.hpp>
#include <sge/opengl/convert/to_gl_enum.hpp>
#include <sge/opengl/state/ffp/sampler/actor_vector.hpp>
#include <sge/opengl/state/ffp/sampler/make_actors.hpp>
#include <sge/opengl/state/ffp/sampler/make_one_op.hpp>
#include <sge/opengl/state/ffp/sampler/set_one.hpp>
#include <sge/renderer/opengl/glinclude.hpp>
#include <sge/renderer/state/ffp/sampler/parameters.hpp>
#include <fcppt/container/join.hpp>

sge::opengl::state::ffp::sampler::actor_vector sge::opengl::state::ffp::sampler::make_actors(
    sge::renderer::state::ffp::sampler::parameters const &_parameters)
{
  return fcppt::container::join(
      sge::opengl::state::ffp::sampler::actor_vector{sge::opengl::state::ffp::sampler::set_one(
          sge::opengl::texture::funcs::env_arg{
              sge::opengl::convert::to_gl_enum<GL_TEXTURE_ENV_MODE>()},
          sge::opengl::texture::funcs::env_int_value{GL_COMBINE})},
      sge::opengl::state::ffp::sampler::make_one_op(_parameters.color_op()),
      sge::opengl::state::ffp::sampler::make_one_op(_parameters.alpha_op()));
}
