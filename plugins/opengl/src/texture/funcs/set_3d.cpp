//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/opengl/call_fun_ref.hpp>
#include <sge/opengl/check_state.hpp>
#include <sge/opengl/color_base_type.hpp>
#include <sge/opengl/color_order.hpp>
#include <sge/opengl/internal_color_format.hpp>
#include <sge/opengl/texture/binding_fwd.hpp>
#include <sge/opengl/texture/buffer_type.hpp>
#include <sge/opengl/texture/volume_config.hpp>
#include <sge/opengl/texture/funcs/set_3d.hpp>
#include <sge/renderer/const_raw_pointer.hpp>
#include <sge/renderer/dim3.hpp>
#include <sge/renderer/opengl/glinclude.hpp>
#include <sge/renderer/texture/creation_failed.hpp>
#include <sge/renderer/texture/mipmap/level.hpp>
#include <fcppt/format.hpp>
#include <fcppt/text.hpp>
#include <fcppt/cast/size.hpp>
#include <fcppt/cast/to_signed.hpp>
#include <fcppt/cast/to_void_ptr.hpp>
#include <fcppt/math/dim/output.hpp> // NOLINT(misc-include-cleaner)

void sge::opengl::texture::funcs::set_3d(
    sge::opengl::texture::binding const &,
    sge::opengl::texture::volume_config const &_config,
    sge::opengl::texture::buffer_type const _buffer_type,
    sge::opengl::color_order const _format,
    sge::opengl::color_base_type const _format_type,
    sge::opengl::internal_color_format const _internal_format,
    sge::renderer::texture::mipmap::level const _level,
    sge::renderer::dim3 const &_dim,
    sge::renderer::const_raw_pointer const _src)
{
  sge::opengl::call_fun_ref(
      _config.tex_image_3d(),
      _buffer_type.get(),
      fcppt::cast::to_signed(_level.get()),
      _internal_format.get(),
      fcppt::cast::size<GLsizei>(fcppt::cast::to_signed(_dim.w())),
      fcppt::cast::size<GLsizei>(fcppt::cast::to_signed(_dim.h())),
      fcppt::cast::size<GLsizei>(fcppt::cast::to_signed(_dim.d())),
      0,
      _format.get(),
      _format_type.get(),
      fcppt::cast::to_void_ptr(_src));

  SGE_OPENGL_CHECK_STATE(
      (fcppt::format(FCPPT_TEXT("Creation of texture with size %1% failed!")) % _dim).str(),
      sge::renderer::texture::creation_failed)
}
