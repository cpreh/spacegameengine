//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_OPENGL_EGL_CURRENT_HPP_INCLUDED
#define SGE_OPENGL_EGL_CURRENT_HPP_INCLUDED

#include <sge/opengl/backend/current.hpp>
#include <sge/opengl/backend/fun_ptr.hpp>
#include <sge/renderer/display_mode/vsync_fwd.hpp>
#include <fcppt/nonmovable.hpp>
#include <fcppt/config/external_begin.hpp>
#include <EGL/egl.h>
#include <string>
#include <fcppt/config/external_end.hpp>


namespace sge::opengl::egl
{

class current
:
	public sge::opengl::backend::current
{
	FCPPT_NONMOVABLE(
		current
	);
public:
	current(
		EGLDisplay,
		EGLSurface
	);

	~current()
	override;
private:
	[[nodiscard]]
	sge::opengl::backend::fun_ptr
	load_function(
		std::string const &
	) const
	override;

	void
	begin_rendering()
	override;

	void
	end_rendering()
	override;

	void
	vsync(
		sge::renderer::display_mode::vsync
	)
	override;

	EGLDisplay const display_; // NOLINT(misc-misplaced-const)

	EGLSurface const surface_; // NOLINT(misc-misplaced-const)
};

}

#endif
