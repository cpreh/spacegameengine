//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_OPENGL_EGL_X11_CREATE_VISUAL_INFO_HPP_INCLUDED
#define SGE_OPENGL_EGL_X11_CREATE_VISUAL_INFO_HPP_INCLUDED

#include <awl/backends/x11/const_display_ref.hpp>
#include <awl/backends/x11/visual/info_unique_ptr.hpp>
#include <fcppt/config/external_begin.hpp>
#include <EGL/egl.h>
#include <fcppt/config/external_end.hpp>


namespace sge::opengl::egl::x11
{

awl::backends::x11::visual::info_unique_ptr
create_visual_info(
	awl::backends::x11::const_display_ref,
	EGLDisplay,
	EGLConfig
);

}

#endif
