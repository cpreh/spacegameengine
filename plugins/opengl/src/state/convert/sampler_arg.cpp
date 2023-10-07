//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/opengl/ext.hpp> // NOLINT(misc-include-cleaner)
#include <sge/opengl/state/convert/sampler_arg.hpp>
#include <sge/renderer/opengl/glinclude.hpp>
#include <sge/renderer/state/ffp/sampler/arg.hpp>
#include <fcppt/assert/unreachable.hpp>

GLenum
sge::opengl::state::convert::sampler_arg(sge::renderer::state::ffp::sampler::arg const _value)
{
  switch (_value)
  {
  case sge::renderer::state::ffp::sampler::arg::previous:
    return GL_PREVIOUS;
  case sge::renderer::state::ffp::sampler::arg::texture:
    return GL_TEXTURE;
  case sge::renderer::state::ffp::sampler::arg::constant:
    return GL_CONSTANT;
  // TODO(philipp): Which extensions do we have to check here?
  case sge::renderer::state::ffp::sampler::arg::vertex_color:
    return GL_PRIMARY_COLOR;
  }

  FCPPT_ASSERT_UNREACHABLE;
}
