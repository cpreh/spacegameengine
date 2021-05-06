//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_OPENGL_EGL_WINDOW_SURFACE_IMPL_HPP_INCLUDED
#define SGE_OPENGL_EGL_WINDOW_SURFACE_IMPL_HPP_INCLUDED

#include <sge/opengl/egl/no_surface.hpp>
#include <sge/opengl/egl/window_surface_decl.hpp>
#include <sge/renderer/exception.hpp>
#include <fcppt/text.hpp>
#include <fcppt/assert/error.hpp>
#include <fcppt/config/external_begin.hpp>
#include <EGL/egl.h>
#include <fcppt/config/external_end.hpp>


template<
	typename NativeWindow
>
sge::opengl::egl::window_surface<
	NativeWindow
>::window_surface(
	EGLDisplay const _display, // NOLINT(misc-misplaced-const)
	EGLConfig const _config, // NOLINT(misc-misplaced-const)
	NativeWindowType const _window
)
:
	display_{
		_display
	},
	surface_{
		::eglCreateWindowSurface(
			_display,
			_config,
			_window,
			nullptr // TODO(philipp): What do we need here?
		)
	}
{
	if(
		surface_
		==
		sge::opengl::egl::no_surface()
	)
	{
		throw
			sge::renderer::exception{
				FCPPT_TEXT("eglCreateWindowSurface failed")
			};
	}
}

namespace sge::opengl::egl
{
template<
	typename NativeWindow
>
window_surface<
	NativeWindow
>::~window_surface()
{
	FCPPT_ASSERT_ERROR(
		::eglDestroySurface(
			display_,
			surface_
		)
		==
		EGL_TRUE
	);
}
}

template<
	typename NativeWindow
>
EGLSurface
sge::opengl::egl::window_surface<
	NativeWindow
>::get() const
{
	return
		surface_;
}

#endif
