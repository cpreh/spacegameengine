//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_OPENGL_WINDOWS_VISUAL_CREATE_HPP_INCLUDED
#define SGE_OPENGL_WINDOWS_VISUAL_CREATE_HPP_INCLUDED

#include <sge/opengl/wgl/visual/config_fwd.hpp>
#include <sge/renderer/pixel_format/object_fwd.hpp>
#include <awl/backends/windows/windows.hpp>
#include <awl/visual/object_unique_ptr.hpp>


namespace sge
{
namespace opengl
{
namespace windows
{
namespace visual
{

awl::visual::object_unique_ptr
create(
	sge::opengl::wgl::visual::config const &,
	sge::renderer::pixel_format::object const &
);

}
}
}
}

#endif
