#include <sge/opengl/egl/visual/base.hpp>
#include <sge/opengl/egl/x11/visual.hpp>
#include <sge/renderer/pixel_format/object_fwd.hpp>
#include <awl/backends/x11/visual/copy_from_parent.hpp>


sge::opengl::egl::x11::visual::visual(
	sge::renderer::pixel_format::object const &_pixel_format
)
:
	awl::backends::x11::visual::copy_from_parent(),
	sge::opengl::egl::visual::base(
		_pixel_format
	)
{
}

sge::opengl::egl::x11::visual::~visual()
{
}
