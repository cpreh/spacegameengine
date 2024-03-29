//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/opengl/state/convert/min_filter.hpp>
#include <sge/renderer/opengl/glinclude.hpp>
#include <sge/renderer/state/core/sampler/filter/normal/min.hpp>
#include <sge/renderer/state/core/sampler/filter/normal/mip.hpp>
#include <fcppt/enum/make_invalid.hpp>
#include <fcppt/preprocessor/disable_gcc_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>

GLenum sge::opengl::state::convert::min_filter(
    sge::renderer::state::core::sampler::filter::normal::min const _min,
    sge::renderer::state::core::sampler::filter::normal::mip const _mip)
{
  FCPPT_PP_PUSH_WARNING
  FCPPT_PP_DISABLE_GCC_WARNING(-Wswitch-default)
  switch (_min)
  {
  case sge::renderer::state::core::sampler::filter::normal::min::point:
    switch (_mip)
    {
    case sge::renderer::state::core::sampler::filter::normal::mip::off:
      return GL_NEAREST;
    case sge::renderer::state::core::sampler::filter::normal::mip::point:
      return GL_NEAREST_MIPMAP_NEAREST;
    case sge::renderer::state::core::sampler::filter::normal::mip::linear:
      return GL_NEAREST_MIPMAP_LINEAR;
    }
    throw fcppt::enum_::make_invalid(_mip);
  case sge::renderer::state::core::sampler::filter::normal::min::linear:
    switch (_mip)
    {
    case sge::renderer::state::core::sampler::filter::normal::mip::off:
      return GL_LINEAR;
    case sge::renderer::state::core::sampler::filter::normal::mip::point:
      return GL_LINEAR_MIPMAP_NEAREST;
    case sge::renderer::state::core::sampler::filter::normal::mip::linear:
      return GL_LINEAR_MIPMAP_LINEAR;
    }
    throw fcppt::enum_::make_invalid(_mip);
  }
  FCPPT_PP_POP_WARNING

  throw fcppt::enum_::make_invalid(_min);
}
