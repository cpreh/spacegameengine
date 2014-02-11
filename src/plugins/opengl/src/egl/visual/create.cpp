#include <sge/opengl/config.hpp>
#include <sge/opengl/egl/visual/create.hpp>
#include <awl/system/object_fwd.hpp>
#include <awl/visual/object_unique_ptr.hpp>
#include <fcppt/make_unique_ptr.hpp>
#if defined(SGE_OPENGL_HAVE_X11)
#include <sge/opengl/egl/x11/visual.hpp>
#else
#error "Implement me!"
#endif


awl::visual::object_unique_ptr
sge::opengl::egl::visual::create(
	awl::system::object &,
	sge::renderer::pixel_format::object const &_pixel_format
)
{
#if defined(SGE_OPENGL_HAVE_X11)
	return
		fcppt::make_unique_ptr<
			sge::opengl::egl::x11::visual
		>(
			_pixel_format
		);
#else
#error "Implement me!"
#endif
}
