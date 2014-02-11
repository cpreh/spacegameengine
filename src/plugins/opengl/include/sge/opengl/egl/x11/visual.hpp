#ifndef SGE_OPENGL_EGL_X11_VISUAL_HPP_INCLUDED
#define SGE_OPENGL_EGL_X11_VISUAL_HPP_INCLUDED

#include <sge/opengl/egl/visual/base.hpp>
#include <sge/renderer/pixel_format/object_fwd.hpp>
#include <awl/backends/x11/visual/copy_from_parent.hpp>
#include <fcppt/noncopyable.hpp>


namespace sge
{
namespace opengl
{
namespace egl
{
namespace x11
{

class visual
:
	public awl::backends::x11::visual::copy_from_parent,
	public sge::opengl::egl::visual::base
{
	FCPPT_NONCOPYABLE(
		visual
	);
public:
	explicit
	visual(
		sge::renderer::pixel_format::object const &
	);

	~visual();
};

}
}
}
}

#endif
