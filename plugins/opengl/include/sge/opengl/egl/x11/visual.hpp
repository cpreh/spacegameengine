//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_OPENGL_EGL_X11_VISUAL_HPP_INCLUDED
#define SGE_OPENGL_EGL_X11_VISUAL_HPP_INCLUDED

#include <sge/opengl/egl/visual/base.hpp>
#include <sge/renderer/pixel_format/object_fwd.hpp>
#include <awl/backends/x11/const_display_ref.hpp>
#include <awl/backends/x11/visual/wrapped.hpp>
#include <fcppt/nonmovable.hpp>
#include <fcppt/log/object_fwd.hpp>
#include <fcppt/config/external_begin.hpp>
#include <EGL/egl.h>
#include <fcppt/config/external_end.hpp>

namespace sge::opengl::egl::x11
{

class visual // NOLINT(fuchsia-multiple-inheritance)
    : public sge::opengl::egl::visual::base,
      public awl::backends::x11::visual::wrapped
{
  FCPPT_NONMOVABLE(visual);

public:
  visual(
      fcppt::log::object &, // NOLINT(google-runtime-references)
      awl::backends::x11::const_display_ref,
      EGLDisplay,
      sge::renderer::pixel_format::object const &);

  ~visual() override;
};

}

#endif
