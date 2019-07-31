//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_OPENGL_WINDOWS_VISUAL_CHOOSE_FORMAT_HPP_INCLUDED
#define SGE_OPENGL_WINDOWS_VISUAL_CHOOSE_FORMAT_HPP_INCLUDED

#include <sge/opengl/windows/gdi_device_fwd.hpp>
#include <sge/opengl/windows/visual/format.hpp>
#include <awl/backends/windows/windows.hpp>


namespace sge
{
namespace opengl
{
namespace windows
{
namespace visual
{

sge::opengl::windows::visual::format const
choose_format(
	sge::opengl::windows::gdi_device const &,
	PIXELFORMATDESCRIPTOR const &
);

}
}
}
}

#endif
