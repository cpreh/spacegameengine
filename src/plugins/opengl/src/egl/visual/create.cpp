#include <sge/opengl/config.hpp>
#include <sge/opengl/egl/init_fwd.hpp>
#include <sge/opengl/egl/visual/create.hpp>
#include <awl/system/object_fwd.hpp>
#include <awl/visual/object_unique_ptr.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/config/external_begin.hpp>
#include <EGL/egl.h>
#include <fcppt/config/external_end.hpp>
#if defined(SGE_OPENGL_HAVE_X11)
#include <sge/opengl/egl/x11/visual.hpp>
#include <awl/backends/x11/system/object.hpp>
#include <fcppt/cast/static_downcast.hpp>
#else
#error "Implement me!"
#endif


awl::visual::object_unique_ptr
sge::opengl::egl::visual::create(
	sge::opengl::egl::init const &,
	awl::system::object &_awl_system,
	EGLDisplay const _egl_display,
	sge::renderer::pixel_format::object const &_pixel_format
)
{
#if defined(SGE_OPENGL_HAVE_X11)
	return
		fcppt::make_unique_ptr<
			sge::opengl::egl::x11::visual
		>(
			fcppt::cast::static_downcast<
				awl::backends::x11::system::object &
			>(
				_awl_system
			).display(),
			_egl_display,
			_pixel_format
		);
#else
#error "Implement me!"
#endif
}
