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


#ifndef SGE_OPENGL_WGL_SYSTEM_HPP_INCLUDED
#define SGE_OPENGL_WGL_SYSTEM_HPP_INCLUDED

#include <sge/opengl/backend/context_unique_ptr.hpp>
#include <sge/opengl/backend/scoped_current_fwd.hpp>
#include <sge/opengl/backend/system.hpp>
#include <sge/opengl/context/system/object_fwd.hpp>
#include <sge/renderer/display_mode/vsync_fwd.hpp>
#include <sge/renderer/pixel_format/object_fwd.hpp>
#include <awl/system/object_fwd.hpp>
#include <awl/visual/object_unique_ptr.hpp>
#include <awl/window/object_fwd.hpp>
#include <fcppt/noncopyable.hpp>


namespace sge
{
namespace opengl
{
namespace wgl
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
		sge::opengl::context::system::object &
	);

	~system();
private:
	awl::visual::object_unique_ptr
	create_visual(
		awl::system::object &,
		sge::renderer::pixel_format::object const &
	);

	sge::opengl::backend::context_unique_ptr
	create_context(
		awl::window::object &
	);

	void
	vsync(
		sge::opengl::backend::scoped_current const &,
		awl::window::object &,
		sge::renderer::display_mode::vsync
	);

	sge::opengl::context::system::object &system_context_;
};

}
}
}

#endif
