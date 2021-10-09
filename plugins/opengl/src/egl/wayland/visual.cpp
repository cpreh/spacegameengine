//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/opengl/egl/visual/base.hpp>
#include <sge/opengl/egl/wayland/visual.hpp>
#include <sge/renderer/pixel_format/object_fwd.hpp>
#include <awl/backends/wayland/visual/null_object.hpp>
#include <fcppt/log/object_fwd.hpp>
#include <fcppt/config/external_begin.hpp>
#include <EGL/egl.h>
#include <fcppt/config/external_end.hpp>

sge::opengl::egl::wayland::visual::visual(
    fcppt::log::object &_log,
    EGLDisplay const _egl_display, // NOLINT(misc-misplaced-const)
    sge::renderer::pixel_format::object const &_pixel_format)
    : sge::opengl::egl::visual::base(_log, _egl_display, _pixel_format),
      awl::backends::wayland::visual::null_object()
{
}

sge::opengl::egl::wayland::visual::~visual() = default;
