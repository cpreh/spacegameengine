#include <sge/opengl/egl/native_display.hpp>
#include <sge/opengl/egl/x11/native_display.hpp>
#include <awl/backends/x11/display.hpp>
#include <awl/backends/x11/window/object.hpp>
#include <fcppt/config/external_begin.hpp>
#include <EGL/egl.h>
#include <fcppt/config/external_end.hpp>


sge::opengl::egl::x11::native_display::native_display(
	awl::backends::x11::window::object &_window
)
:
	display_(
		_window.display().get()
	)
{
}

sge::opengl::egl::x11::native_display::~native_display()
{
}

EGLNativeDisplayType
sge::opengl::egl::x11::native_display::get() const
{
	return
		display_;
}
