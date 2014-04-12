/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2013 Carl Philipp Reh (sefi@s-e-f-i.de)

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU Lesser General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
*/


#ifndef SGE_OPENGL_EGL_CONTEXT_HPP_INCLUDED
#define SGE_OPENGL_EGL_CONTEXT_HPP_INCLUDED

#include <sge/opengl/backend/context.hpp>
#include <sge/opengl/egl/context_impl.hpp>
#include <sge/opengl/egl/init.hpp>
#include <sge/opengl/egl/native_display_unique_ptr.hpp>
#include <sge/opengl/egl/window_surface.hpp>
#include <awl/visual/object_fwd.hpp>
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

class context
:
	public sge::opengl::backend::context
{
	FCPPT_NONCOPYABLE(
		context
	);
public:
	context(
		sge::opengl::egl::native_display_unique_ptr &&,
		EGLNativeWindowType,
		awl::visual::object const &
	);

	~context()
	override;
private:
	void
	activate()
	override;

	void
	deactivate()
	override;

	void
	begin_rendering()
	override;

	void
	end_rendering()
	override;

	sge::opengl::egl::native_display_unique_ptr const native_display_;

	EGLDisplay const display_;

	sge::opengl::egl::init const init_;

	EGLConfig const config_;

	sge::opengl::egl::window_surface const surface_;

	sge::opengl::egl::context_impl context_;
};

}
}
}

#endif
