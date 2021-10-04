//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_OPENGL_EGL_WAYLAND_DISPLAY_HPP_INCLUDED
#define SGE_OPENGL_EGL_WAYLAND_DISPLAY_HPP_INCLUDED

#include <sge/opengl/egl/display.hpp>
#include <sge/opengl/egl/init_fwd.hpp>
#include <sge/opengl/egl/surface_unique_ptr.hpp>
#include <sge/renderer/pixel_format/object_fwd.hpp>
#include <sge/window/object_ref.hpp>
#include <awl/backends/wayland/system/object_ref.hpp>
#include <awl/visual/object_unique_ptr.hpp>
#include <fcppt/nonmovable.hpp>
#include <fcppt/log/object_reference.hpp>
#include <fcppt/config/external_begin.hpp>
#include <EGL/egl.h>
#include <fcppt/config/external_end.hpp>


namespace sge::opengl::egl::wayland
{

class display
:
	public sge::opengl::egl::display
{
	FCPPT_NONMOVABLE(
		display
	);
public:
	display(
		fcppt::log::object_reference,
		awl::backends::wayland::system::object_ref
	);

	~display()
	override;
private:
	[[nodiscard]]
	EGLDisplay
	get() const
	override;

	[[nodiscard]]
	awl::visual::object_unique_ptr
	create_visual(
		sge::opengl::egl::init const &,
		sge::renderer::pixel_format::object const &
	)
	override;

	[[nodiscard]]
	sge::opengl::egl::surface_unique_ptr
	create_surface(
		EGLConfig,
		sge::window::object_ref
	)
	override;

	fcppt::log::object_reference const log_;

	EGLDisplay const display_; // NOLINT(misc-misplaced-const)
};

}

#endif
