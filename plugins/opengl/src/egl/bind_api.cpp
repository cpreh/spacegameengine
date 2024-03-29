//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/opengl/egl/bind_api.hpp>
#include <sge/renderer/exception.hpp>
#include <fcppt/text.hpp>
#include <fcppt/config/external_begin.hpp>
#include <EGL/egl.h>
#include <fcppt/config/external_end.hpp>

void sge::opengl::egl::bind_api(EGLenum const _api)
{
  if (::eglBindAPI(_api) != EGL_TRUE)
  {
    throw sge::renderer::exception{FCPPT_TEXT("eglBindAPI failed")};
  }
}
