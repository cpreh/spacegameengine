//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_OPENGL_EGL_CONTEXT_HPP_INCLUDED
#define SGE_OPENGL_EGL_CONTEXT_HPP_INCLUDED

#include <sge/opengl/backend/context.hpp>
#include <sge/opengl/backend/current_unique_ptr.hpp>
#include <sge/opengl/egl/context_impl.hpp>
#include <sge/opengl/egl/surface_unique_ptr.hpp>
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

class context
:
	public sge::opengl::backend::context
{
	FCPPT_NONCOPYABLE(
		context
	);
public:
	context(
		EGLDisplay,
		EGLConfig,
		sge::opengl::egl::surface_unique_ptr &&
	);

	~context()
	override;
private:
	sge::opengl::backend::current_unique_ptr
	activate()
	override;

	void
	deactivate(
		sge::opengl::backend::current_unique_ptr &&
	)
	override;

	EGLDisplay const display_;

	sge::opengl::egl::surface_unique_ptr const surface_;

	sge::opengl::egl::context_impl context_;
};

}
}
}

#endif
