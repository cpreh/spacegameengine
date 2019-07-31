//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_OPENGL_EGL_X11_DISPLAY_HPP_INCLUDED
#define SGE_OPENGL_EGL_X11_DISPLAY_HPP_INCLUDED

#include <sge/opengl/egl/display.hpp>
#include <sge/opengl/egl/init_fwd.hpp>
#include <sge/opengl/egl/surface_unique_ptr.hpp>
#include <sge/renderer/pixel_format/object_fwd.hpp>
#include <sge/window/object_fwd.hpp>
#include <awl/backends/x11/display_fwd.hpp>
#include <awl/backends/x11/system/object_fwd.hpp>
#include <awl/visual/object_unique_ptr.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/log/object_fwd.hpp>
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

class display
:
	public sge::opengl::egl::display
{
	FCPPT_NONCOPYABLE(
		display
	);
public:
	display(
		fcppt::log::object &,
		awl::backends::x11::system::object &
	);

	~display()
	override;
private:
	EGLDisplay
	get() const
	override;

	awl::visual::object_unique_ptr
	create_visual(
		sge::opengl::egl::init const &,
		sge::renderer::pixel_format::object const &
	)
	override;

	sge::opengl::egl::surface_unique_ptr
	create_surface(
		EGLConfig,
		sge::window::object &
	)
	override;

	fcppt::log::object &log_;

	awl::backends::x11::display &x11_display_;

	EGLDisplay const display_;
};

}
}
}
}

#endif
