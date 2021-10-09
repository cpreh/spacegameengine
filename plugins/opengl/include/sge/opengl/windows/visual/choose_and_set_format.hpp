//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_OPENGL_WINDOWS_VISUAL_CHOOSE_AND_SET_FORMAT_HPP_INCLUDED
#define SGE_OPENGL_WINDOWS_VISUAL_CHOOSE_AND_SET_FORMAT_HPP_INCLUDED

#include <sge/opengl/wgl/visual/config_fwd.hpp>
#include <sge/renderer/pixel_format/object_fwd.hpp>
#include <awl/backends/windows/windows.hpp>

namespace sge
{
namespace opengl
{
namespace windows
{
namespace visual
{

void choose_and_set_format(
    sge::opengl::wgl::visual::config const &, HWND, sge::renderer::pixel_format::object const &);

}
}
}
}

#endif
