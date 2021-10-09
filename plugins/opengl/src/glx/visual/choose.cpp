//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/opengl/glx/visual/attribute_container.hpp>
#include <sge/opengl/glx/visual/choose.hpp>
#include <sge/renderer/exception.hpp>
#include <awl/backends/x11/display.hpp>
#include <awl/backends/x11/screen.hpp>
#include <awl/backends/x11/visual/info_unique_ptr.hpp>
#include <fcppt/text.hpp>
#include <fcppt/config/external_begin.hpp>
#include <GL/glx.h>
#include <fcppt/config/external_end.hpp>

awl::backends::x11::visual::info_unique_ptr sge::opengl::glx::visual::choose(
    awl::backends::x11::display const &_display,
    awl::backends::x11::screen const _screen,
    sge::opengl::glx::visual::attribute_container const &_attributes)
{
  XVisualInfo *const info{::glXChooseVisual(
      _display.get(),
      _screen.get(),
      // NOLINTNEXTLINE(cppcoreguidelines-pro-type-const-cast)
      const_cast<int *>(_attributes.data()))};

  if (info == nullptr)
  {
    throw sge::renderer::exception{FCPPT_TEXT("glXChooseVisual() failed!")};
  }

  return awl::backends::x11::visual::info_unique_ptr{info};
}
