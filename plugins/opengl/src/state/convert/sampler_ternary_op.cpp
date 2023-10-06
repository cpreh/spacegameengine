//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/opengl/ext.hpp>
#include <sge/opengl/state/convert/sampler_ternary_op.hpp>
#include <sge/renderer/opengl/glinclude.hpp>
#include <sge/renderer/state/ffp/sampler/ternary_op_type.hpp>
#include <fcppt/assert/unreachable.hpp>

GLenum sge::opengl::state::convert::sampler_ternary_op(
    sge::renderer::state::ffp::sampler::ternary_op_type const _op)
{
  switch (_op)
  {
  case sge::renderer::state::ffp::sampler::ternary_op_type::interpolate:
    return GL_INTERPOLATE;
  }

  FCPPT_ASSERT_UNREACHABLE;
}
