//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/opengl/wgl/make_current.hpp>
#include <sge/renderer/exception.hpp>
#include <awl/backends/windows/windows.hpp>
#include <fcppt/text.hpp>

void sge::opengl::wgl::make_current(HDC const _dc, HGLRC const _glrc)
{
  if (::wglMakeCurrent(_dc, _glrc) == FALSE)
    throw sge::renderer::exception(FCPPT_TEXT("wglMakeCurrent() failed!"));
}
