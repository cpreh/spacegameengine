//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_OPENGL_WGL_VISUAL_MAKE_ATTRIBUTES_HPP_INCLUDED
#define SGE_OPENGL_WGL_VISUAL_MAKE_ATTRIBUTES_HPP_INCLUDED

#include <sge/opengl/wgl/visual/attribute_container.hpp>
#include <sge/opengl/wgl/visual/config_fwd.hpp>
#include <sge/renderer/pixel_format/object_fwd.hpp>

namespace sge
{
namespace opengl
{
namespace wgl
{
namespace visual
{

sge::opengl::wgl::visual::attribute_container make_attributes(
    sge::opengl::wgl::visual::config const &, sge::renderer::pixel_format::object const &);

}
}
}
}

#endif
