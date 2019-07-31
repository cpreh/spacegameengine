//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_OPENGL_EGL_CONTEXT_IMPL_HPP_INCLUDED
#define SGE_OPENGL_EGL_CONTEXT_IMPL_HPP_INCLUDED

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

class context_impl
{
	FCPPT_NONCOPYABLE(
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
	EGLDisplay const display_;

	EGLContext const context_;
};

}
}
}

#endif
