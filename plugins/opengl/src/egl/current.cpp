//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/opengl/backend/current.hpp>
#include <sge/opengl/backend/fun_ptr.hpp>
#include <sge/opengl/egl/current.hpp>
#include <sge/opengl/egl/swap_buffers.hpp>
#include <sge/renderer/display_mode/vsync.hpp>
#include <fcppt/config/external_begin.hpp>
#include <EGL/egl.h>
#include <string>
#include <fcppt/config/external_end.hpp>

sge::opengl::egl::current::current(display_type const _display, surface_type const _surface)
    : sge::opengl::backend::current(), display_{_display.get()}, surface_{_surface.get()}
{
}

sge::opengl::egl::current::~current() = default;

sge::opengl::backend::fun_ptr
sge::opengl::egl::current::load_function(std::string const &_name) const
{
  return ::eglGetProcAddress(_name.c_str());
}

void sge::opengl::egl::current::begin_rendering() {}

void sge::opengl::egl::current::end_rendering()
{
  sge::opengl::egl::swap_buffers(display_, surface_);
}

void sge::opengl::egl::current::vsync(sge::renderer::display_mode::vsync const _vsync) {}
