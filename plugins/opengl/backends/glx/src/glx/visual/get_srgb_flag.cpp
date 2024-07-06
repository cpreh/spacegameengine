//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/opengl/glx/extension.hpp>
#include <sge/opengl/glx/extension_set.hpp>
#include <sge/opengl/glx/extension_supported.hpp>
#include <sge/opengl/glx/visual/get_srgb_flag.hpp>
#include <sge/opengl/glx/visual/optional_srgb_flag.hpp>
#include <sge/opengl/glx/visual/srgb_flag.hpp>
#include <fcppt/optional/make_if.hpp>
#include <fcppt/config/external_begin.hpp>
#include <GL/glx.h> // NOLINT(misc-include-cleaner)
#include <GL/glxext.h>
#include <fcppt/config/external_end.hpp>

sge::opengl::glx::visual::optional_srgb_flag
sge::opengl::glx::visual::get_srgb_flag(sge::opengl::glx::extension_set const &_extensions)
{
  return sge::opengl::glx::extension_supported(
             _extensions, sge::opengl::glx::extension{"GLX_EXT_framebuffer_sRGB"})
             ? sge::opengl::glx::visual::optional_srgb_flag{sge::opengl::glx::visual::srgb_flag{
                   GLX_FRAMEBUFFER_SRGB_CAPABLE_EXT}}
             : fcppt::optional::make_if(
                   sge::opengl::glx::extension_supported(
                       _extensions, sge::opengl::glx::extension{"GLX_ARB_framebuffer_sRGB"}),
                   [] {
                     return sge::opengl::glx::visual::srgb_flag{GLX_FRAMEBUFFER_SRGB_CAPABLE_ARB};
                   });
}
