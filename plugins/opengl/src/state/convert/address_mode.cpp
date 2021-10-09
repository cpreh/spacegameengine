//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/opengl/common.hpp>
#include <sge/opengl/state/convert/address_mode.hpp>
#include <sge/renderer/state/core/sampler/address/mode.hpp>
#include <fcppt/assert/unreachable.hpp>

GLenum sge::opengl::state::convert::address_mode(
    sge::renderer::state::core::sampler::address::mode const _mode)
{
  switch (_mode)
  {
  case sge::renderer::state::core::sampler::address::mode::clamp:
    return GL_CLAMP;
  case sge::renderer::state::core::sampler::address::mode::mirror_repeat:
    return GL_MIRRORED_REPEAT;
  case sge::renderer::state::core::sampler::address::mode::repeat:
    return GL_REPEAT;
  }

  FCPPT_ASSERT_UNREACHABLE;
}
