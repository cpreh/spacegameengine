//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/image/ds/format.hpp>
#include <sge/opengl/fbo/config.hpp>
#include <sge/opengl/fbo/depth_stencil_format_to_attachment.hpp>
#include <sge/opengl/fbo/optional_attachment_type.hpp>
#include <fcppt/assert/unreachable.hpp>

sge::opengl::fbo::optional_attachment_type sge::opengl::fbo::depth_stencil_format_to_attachment(
    sge::opengl::fbo::config const &_context, sge::image::ds::format const _format)
{
  switch (_format)
  {
  case sge::image::ds::format::d16:
  case sge::image::ds::format::d32:
    return sge::opengl::fbo::optional_attachment_type(_context.depth_attachment());
  case sge::image::ds::format::d24s8:
    return _context.depth_stencil_attachment();
  }

  FCPPT_ASSERT_UNREACHABLE;
}
