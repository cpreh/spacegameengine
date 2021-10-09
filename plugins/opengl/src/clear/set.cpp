//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/opengl/call.hpp>
#include <sge/opengl/check_state.hpp>
#include <sge/opengl/common.hpp>
#include <sge/opengl/clear/back_buffer.hpp>
#include <sge/opengl/clear/depth_buffer.hpp>
#include <sge/opengl/clear/set.hpp>
#include <sge/opengl/clear/stencil_buffer.hpp>
#include <sge/renderer/exception.hpp>
#include <sge/renderer/clear/back_buffer_value.hpp>
#include <sge/renderer/clear/depth_buffer_value.hpp>
#include <sge/renderer/clear/parameters.hpp>
#include <sge/renderer/clear/stencil_buffer_value.hpp>
#include <fcppt/text.hpp>
#include <fcppt/optional/maybe_void.hpp>

void sge::opengl::clear::set(sge::renderer::clear::parameters const &_parameters)
{
  GLenum flags(0);

  fcppt::optional::maybe_void(
      _parameters.back_buffer(),
      [&flags](sge::renderer::clear::back_buffer_value const &_back_buffer)
      {
        flags |= GL_COLOR_BUFFER_BIT; // NOLINT(hicpp-signed-bitwise)

        sge::opengl::clear::back_buffer(_back_buffer);
      });

  fcppt::optional::maybe_void(
      _parameters.depth_buffer(),
      [&flags](sge::renderer::clear::depth_buffer_value const _depth_buffer)
      {
        flags |= GL_DEPTH_BUFFER_BIT; // NOLINT(hicpp-signed-bitwise)

        sge::opengl::clear::depth_buffer(_depth_buffer);
      });

  fcppt::optional::maybe_void(
      _parameters.stencil_buffer(),
      [&flags](sge::renderer::clear::stencil_buffer_value const _stencil_buffer)
      {
        flags |= GL_STENCIL_BUFFER_BIT; // NOLINT(hicpp-signed-bitwise)

        sge::opengl::clear::stencil_buffer(_stencil_buffer);
      });

  sge::opengl::call(::glClear, flags);

  SGE_OPENGL_CHECK_STATE(FCPPT_TEXT("glClear failed"), sge::renderer::exception)
}
