//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/image/ds/format.hpp>
#include <sge/opengl/fbo/config.hpp>
#include <sge/opengl/fbo/depth_stencil_format_to_attachment.hpp>
#include <sge/opengl/fbo/optional_attachment_type.hpp>
#include <fcppt/enum/make_invalid.hpp>
#include <fcppt/preprocessor/disable_gcc_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>

sge::opengl::fbo::optional_attachment_type sge::opengl::fbo::depth_stencil_format_to_attachment(
    sge::opengl::fbo::config const &_context, sge::image::ds::format const _format)
{
  FCPPT_PP_PUSH_WARNING
  FCPPT_PP_DISABLE_GCC_WARNING(-Wswitch-default)
  switch (_format)
  {
  case sge::image::ds::format::d16:
  case sge::image::ds::format::d32:
    return sge::opengl::fbo::optional_attachment_type(_context.depth_attachment());
  case sge::image::ds::format::d24s8:
    return _context.depth_stencil_attachment();
  }
  FCPPT_PP_POP_WARNING

  throw fcppt::enum_::make_invalid(_format);
}
