//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_OPENGL_EGL_X11_SURFACE_HPP_INCLUDED
#define SGE_OPENGL_EGL_X11_SURFACE_HPP_INCLUDED

#include <sge/opengl/egl/surface.hpp>
#include <sge/opengl/egl/window_surface_decl.hpp>
#include <awl/backends/x11/window/const_base_ref.hpp>
#include <fcppt/nonmovable.hpp>
#include <fcppt/config/external_begin.hpp>
#include <EGL/egl.h>
#include <fcppt/config/external_end.hpp>


namespace sge::opengl::egl::x11
{

class surface
:
	public sge::opengl::egl::surface
{
	FCPPT_NONMOVABLE(
		surface
	);
public:
	surface(
		EGLDisplay,
		EGLConfig,
		awl::backends::x11::window::const_base_ref
	);

	~surface()
	override;
private:
	[[nodiscard]]
	EGLSurface
	get() const
	override;

	sge::opengl::egl::window_surface<
		EGLNativeWindowType
	> const surface_;
};

}

#endif
