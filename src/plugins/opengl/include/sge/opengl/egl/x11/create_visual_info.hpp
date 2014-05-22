#ifndef SGE_OPENGL_EGL_X11_CREATE_VISUAL_INFO_HPP_INCLUDED
#define SGE_OPENGL_EGL_X11_CREATE_VISUAL_INFO_HPP_INCLUDED

#include <awl/backends/x11/display_fwd.hpp>
#include <awl/backends/x11/visual/info_unique_ptr.hpp>
#include <fcppt/config/external_begin.hpp>
#include <EGL/egl.h>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace opengl
{
namespace egl
{
namespace x11
{

awl::backends::x11::visual::info_unique_ptr
create_visual_info(
	awl::backends::x11::display const &,
	EGLDisplay,
	EGLConfig
);

}
}
}
}

#endif
