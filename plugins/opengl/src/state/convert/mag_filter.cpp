//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/opengl/common.hpp>
#include <sge/opengl/state/convert/mag_filter.hpp>
#include <sge/renderer/state/core/sampler/filter/normal/mag.hpp>
#include <fcppt/assert/unreachable.hpp>

GLenum sge::opengl::state::convert::mag_filter(
    sge::renderer::state::core::sampler::filter::normal::mag const _filter)
{
  switch (_filter)
  {
  case sge::renderer::state::core::sampler::filter::normal::mag::point:
    return GL_NEAREST;
  case sge::renderer::state::core::sampler::filter::normal::mag::linear:
    return GL_LINEAR;
  }

  FCPPT_ASSERT_UNREACHABLE;
}
