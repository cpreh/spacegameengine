//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_OPENGL_EGL_DISPLAY_HPP_INCLUDED
#define SGE_OPENGL_EGL_DISPLAY_HPP_INCLUDED

#include <sge/opengl/egl/display_fwd.hpp>
#include <sge/opengl/egl/init_fwd.hpp>
#include <sge/opengl/egl/surface_unique_ptr.hpp>
#include <sge/renderer/pixel_format/object_fwd.hpp>
#include <sge/window/object_fwd.hpp>
#include <awl/visual/object_unique_ptr.hpp>
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

class display
{
	FCPPT_NONCOPYABLE(
		display
	);
protected:
	display();
public:
	virtual
	~display() = 0;

	virtual
	EGLDisplay
	get() const = 0;

	virtual
	awl::visual::object_unique_ptr
	create_visual(
		sge::opengl::egl::init const &,
		sge::renderer::pixel_format::object const &
	) = 0;

	virtual
	sge::opengl::egl::surface_unique_ptr
	create_surface(
		EGLConfig,
		sge::window::object &
	) = 0;
};

}
}
}

#endif
