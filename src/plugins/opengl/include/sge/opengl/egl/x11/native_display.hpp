#ifndef SGE_OPENGL_EGL_X11_NATIVE_DISPLAY_HPP_INCLUDED
#define SGE_OPENGL_EGL_X11_NATIVE_DISPLAY_HPP_INCLUDED

#include <sge/opengl/egl/native_display.hpp>
#include <awl/backends/x11/window/object_fwd.hpp>
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
namespace x11
{

class native_display
:
	public sge::opengl::egl::native_display
{
	FCPPT_NONCOPYABLE(
		native_display
	);
public:
	explicit
	native_display(
		awl::backends::x11::window::object &
	);

	~native_display()
	override;
private:
	EGLNativeDisplayType
	get() const
	override;

	EGLNativeDisplayType const display_;
};

}
}
}
}

#endif
