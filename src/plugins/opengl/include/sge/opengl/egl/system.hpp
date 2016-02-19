/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2016 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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


#ifndef SGE_OPENGL_EGL_SYSTEM_HPP_INCLUDED
#define SGE_OPENGL_EGL_SYSTEM_HPP_INCLUDED

#include <sge/opengl/backend/context_unique_ptr.hpp>
#include <sge/opengl/backend/system.hpp>
#include <sge/opengl/egl/init.hpp>
#include <sge/opengl/egl/native_display_unique_ptr.hpp>
#include <sge/renderer/pixel_format/object_fwd.hpp>
#include <awl/system/object_fwd.hpp>
#include <awl/visual/object_unique_ptr.hpp>
#include <awl/window/object_fwd.hpp>
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

class system
:
	public sge::opengl::backend::system
{
	FCPPT_NONCOPYABLE(
		system
	);
public:
	explicit
	system(
		awl::system::object &
	);

	~system()
	override;
private:
	awl::visual::object_unique_ptr
	create_visual(
		sge::renderer::pixel_format::object const &
	)
	override;

	sge::opengl::backend::context_unique_ptr
	create_context(
		awl::window::object &
	)
	override;

	awl::system::object &awl_system_;

	sge::opengl::egl::native_display_unique_ptr const egl_native_display_;

	EGLDisplay const egl_display_;

	sge::opengl::egl::init const init_;
};

}
}
}

#endif
