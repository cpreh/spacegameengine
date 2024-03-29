//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/opengl/ext.hpp>
#include <sge/opengl/state/convert/address_mode.hpp>
#include <sge/renderer/opengl/glinclude.hpp>
#include <sge/renderer/state/core/sampler/address/mode.hpp>
#include <fcppt/enum/make_invalid.hpp>
#include <fcppt/preprocessor/disable_gcc_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>

GLenum sge::opengl::state::convert::address_mode(
    sge::renderer::state::core::sampler::address::mode const _mode)
{
  FCPPT_PP_PUSH_WARNING
  FCPPT_PP_DISABLE_GCC_WARNING(-Wswitch-default)
  switch (_mode)
  {
  case sge::renderer::state::core::sampler::address::mode::clamp:
    return GL_CLAMP;
  case sge::renderer::state::core::sampler::address::mode::mirror_repeat:
    return GL_MIRRORED_REPEAT;
  case sge::renderer::state::core::sampler::address::mode::repeat:
    return GL_REPEAT;
  }
  FCPPT_PP_POP_WARNING

  throw fcppt::enum_::make_invalid(_mode);
}
