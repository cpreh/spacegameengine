//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/opengl/common.hpp>
#include <sge/opengl/state/convert/sampler_binary_op.hpp>
#include <sge/opengl/state/convert/sampler_op.hpp>
#include <sge/opengl/state/convert/sampler_ternary_op.hpp>
#include <sge/opengl/state/convert/sampler_unary_op.hpp>
#include <sge/renderer/state/ffp/sampler/binary_op_type.hpp>
#include <sge/renderer/state/ffp/sampler/ternary_op_type.hpp>
#include <sge/renderer/state/ffp/sampler/unary_op_type.hpp>

GLenum sge::opengl::state::convert::sampler_op(
    sge::renderer::state::ffp::sampler::unary_op_type const _unary_op)
{
  return sge::opengl::state::convert::sampler_unary_op(_unary_op);
}

GLenum sge::opengl::state::convert::sampler_op(
    sge::renderer::state::ffp::sampler::binary_op_type const _binary_op)
{
  return sge::opengl::state::convert::sampler_binary_op(_binary_op);
}

GLenum sge::opengl::state::convert::sampler_op(
    sge::renderer::state::ffp::sampler::ternary_op_type const _ternary_op)
{
  return sge::opengl::state::convert::sampler_ternary_op(_ternary_op);
}
