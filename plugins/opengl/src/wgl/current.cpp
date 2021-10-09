//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/opengl/backend/current.hpp>
#include <sge/opengl/wgl/current.hpp>
#include <sge/opengl/wgl/get_proc_address.hpp>
#include <sge/opengl/windows/gdi_device.hpp>
#include <sge/renderer/exception.hpp>
#include <sge/renderer/display_mode/vsync.hpp>
#include <awl/backends/windows/windows.hpp>
#include <fcppt/text.hpp>

sge::opengl::wgl::current::current(sge::opengl::windows::gdi_device const &_gdi_device)
    : sge::opengl::backend::current(), gdi_device_(_gdi_device)
{
}

sge::opengl::wgl::current::~current() {}

sge::opengl::backend::fun_ptr
sge::opengl::wgl::current::load_function(std::string const &_name) const
{
  return reinterpret_cast<sge::opengl::backend::fun_ptr>(sge::opengl::wgl::get_proc_address(_name));
}

void sge::opengl::wgl::current::begin_rendering() {}

void sge::opengl::wgl::current::end_rendering()
{
  if (::wglSwapLayerBuffers(gdi_device_.hdc(), WGL_SWAP_MAIN_PLANE) == FALSE)
    throw sge::renderer::exception(FCPPT_TEXT("wglSwapLayerBuffers() failed!"));
}

void sge::opengl::wgl::current::vsync(sge::renderer::display_mode::vsync const _vsync) {}
