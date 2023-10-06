//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/opengl/call.hpp>
#include <sge/opengl/check_state.hpp>
#include <sge/opengl/color_base_type.hpp>
#include <sge/opengl/color_order.hpp>
#include <sge/opengl/texture/binding_fwd.hpp>
#include <sge/opengl/texture/buffer_type.hpp>
#include <sge/opengl/texture/funcs/get_image.hpp>
#include <sge/renderer/exception.hpp>
#include <sge/renderer/raw_pointer.hpp>
#include <sge/renderer/opengl/glinclude.hpp>
#include <sge/renderer/texture/mipmap/level.hpp>
#include <fcppt/text.hpp>
#include <fcppt/cast/to_signed.hpp>
#include <fcppt/cast/to_void_ptr.hpp>

void sge::opengl::texture::funcs::get_image(
    sge::opengl::texture::binding const &,
    sge::opengl::texture::buffer_type const _buffer_type,
    sge::opengl::color_order const _format,
    sge::opengl::color_base_type const _format_type,
    sge::renderer::raw_pointer const _dest,
    sge::renderer::texture::mipmap::level const _level)
{
  sge::opengl::call(
      ::glGetTexImage,
      _buffer_type.get(),
      fcppt::cast::to_signed(_level.get()),
      _format.get(),
      _format_type.get(),
      fcppt::cast::to_void_ptr(_dest));

  SGE_OPENGL_CHECK_STATE(FCPPT_TEXT("glGetTexImage failed"), sge::renderer::exception)
}
