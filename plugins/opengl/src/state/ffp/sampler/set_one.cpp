//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/opengl/convert/to_gl_enum.hpp>
#include <sge/opengl/state/ffp/sampler/actor.hpp>
#include <sge/opengl/state/ffp/sampler/set_one.hpp>
#include <sge/opengl/texture/active_level_fwd.hpp>
#include <sge/opengl/texture/funcs/env_arg.hpp>
#include <sge/opengl/texture/funcs/env_int.hpp>
#include <sge/opengl/texture/funcs/env_int_value.hpp>
#include <sge/opengl/texture/funcs/env_target.hpp>
#include <sge/renderer/opengl/glinclude.hpp>

sge::opengl::state::ffp::sampler::actor sge::opengl::state::ffp::sampler::set_one(
    sge::opengl::texture::funcs::env_arg const _arg,
    sge::opengl::texture::funcs::env_int_value const _value)
{
  return sge::opengl::state::ffp::sampler::actor{
      [_arg, _value](sge::opengl::texture::active_level const &_level)
      {
        sge::opengl::texture::funcs::env_int(
            _level,
            sge::opengl::texture::funcs::env_target{
                sge::opengl::convert::to_gl_enum<GL_TEXTURE_ENV>()},
            _arg,
            _value);
      }};
}
