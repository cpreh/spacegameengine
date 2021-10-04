//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_OPENGL_EGL_CONTEXT_IMPL_HPP_INCLUDED
#define SGE_OPENGL_EGL_CONTEXT_IMPL_HPP_INCLUDED

#include <fcppt/nonmovable.hpp>
#include <fcppt/config/external_begin.hpp>
#include <EGL/egl.h>
#include <fcppt/config/external_end.hpp>


namespace sge::opengl::egl
{

class context_impl
{
	FCPPT_NONMOVABLE(
		context_impl
	);
public:
	context_impl(
		EGLDisplay,
		EGLConfig
	);

	~context_impl();

	void
	activate(
		EGLSurface
	);

	void
	deactivate();
private:
	EGLDisplay const display_; // NOLINT(misc-misplaced-const)

	EGLContext const context_; // NOLINT(misc-misplaced-const)
};

}

#endif
