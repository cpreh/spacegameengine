//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/opengl/state/convert/mag_filter.hpp>
#include <sge/renderer/opengl/glinclude.hpp>
#include <sge/renderer/state/core/sampler/filter/normal/mag.hpp>
#include <fcppt/enum/make_invalid.hpp>
#include <fcppt/preprocessor/disable_gcc_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>

GLenum sge::opengl::state::convert::mag_filter(
    sge::renderer::state::core::sampler::filter::normal::mag const _filter)
{
  FCPPT_PP_PUSH_WARNING
  FCPPT_PP_DISABLE_GCC_WARNING(-Wswitch-default)
  switch (_filter)
  {
  case sge::renderer::state::core::sampler::filter::normal::mag::point:
    return GL_NEAREST;
  case sge::renderer::state::core::sampler::filter::normal::mag::linear:
    return GL_LINEAR;
  }
  FCPPT_PP_POP_WARNING

  throw fcppt::enum_::make_invalid(_filter);
}
