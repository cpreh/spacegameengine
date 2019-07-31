//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_OPENGL_EGL_WINDOW_SURFACE_DECL_HPP_INCLUDED
#define SGE_OPENGL_EGL_WINDOW_SURFACE_DECL_HPP_INCLUDED

#include <sge/opengl/egl/window_surface_fwd.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/config/external_begin.hpp>
#include <EGL/egl.h>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace opengl
{
namespace egl
{

template<
	typename NativeWindow
>
class window_surface
{
	FCPPT_NONCOPYABLE(
		window_surface
	);
public:
	window_surface(
		EGLDisplay,
		EGLConfig,
		NativeWindowType
	);

	~window_surface();

	EGLSurface
	get() const;
private:
	EGLDisplay const display_;

	EGLSurface const surface_;
};

}
}
}

#endif
