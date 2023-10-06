//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/opengl/ext.hpp>
#include <sge/opengl/state/convert/sampler_color_arg_type.hpp>
#include <sge/renderer/opengl/glinclude.hpp>
#include <sge/renderer/state/ffp/sampler/arg1.hpp>
#include <sge/renderer/state/ffp/sampler/arg2.hpp>
#include <sge/renderer/state/ffp/sampler/arg3.hpp>

GLenum
sge::opengl::state::convert::sampler_color_arg_type<sge::renderer::state::ffp::sampler::arg1>::get()
{
  return GL_SRC0_RGB;
}

GLenum
sge::opengl::state::convert::sampler_color_arg_type<sge::renderer::state::ffp::sampler::arg2>::get()
{
  return GL_SRC1_RGB;
}

GLenum
sge::opengl::state::convert::sampler_color_arg_type<sge::renderer::state::ffp::sampler::arg3>::get()
{
  return GL_SRC2_RGB;
}
