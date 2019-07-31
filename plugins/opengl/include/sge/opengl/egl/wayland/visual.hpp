//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_OPENGL_EGL_WAYLAND_VISUAL_HPP_INCLUDED
#define SGE_OPENGL_EGL_WAYLAND_VISUAL_HPP_INCLUDED

#include <sge/opengl/egl/visual/base.hpp>
#include <sge/renderer/pixel_format/object_fwd.hpp>
#include <awl/backends/wayland/visual/null_object.hpp>
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
namespace wayland
{

class visual
:
	public sge::opengl::egl::visual::base,
	public awl::backends::wayland::visual::null_object
{
	FCPPT_NONCOPYABLE(
		visual
	);
public:
	visual(
		fcppt::log::object &,
		EGLDisplay,
		sge::renderer::pixel_format::object const &
	);

	~visual()
	override;
};

}
}
}
}

#endif
