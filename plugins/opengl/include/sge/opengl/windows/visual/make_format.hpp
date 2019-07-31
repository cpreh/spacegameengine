//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_OPENGL_WINDOWS_VISUAL_MAKE_FORMAT_HPP_INCLUDED
#define SGE_OPENGL_WINDOWS_VISUAL_MAKE_FORMAT_HPP_INCLUDED

#include <sge/renderer/pixel_format/color_fwd.hpp>
#include <sge/renderer/pixel_format/depth_stencil_fwd.hpp>
#include <awl/backends/windows/windows.hpp>


namespace sge
{
namespace opengl
{
namespace windows
{
namespace visual
{

PIXELFORMATDESCRIPTOR const
make_format(
	sge::renderer::pixel_format::color,
	sge::renderer::pixel_format::depth_stencil
);

}
}
}
}

#endif
