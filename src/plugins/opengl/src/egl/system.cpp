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


#include <sge/opengl/device_state/context_unique_ptr.hpp>
#include <sge/opengl/device_state/scoped_current_fwd.hpp>
#include <sge/opengl/device_state/system.hpp>
#include <sge/opengl/egl/context.hpp>
#include <sge/opengl/egl/create_native_display.hpp>
#include <sge/opengl/egl/native_display.hpp>
#include <sge/opengl/egl/native_window.hpp>
#include <sge/opengl/egl/system.hpp>
#include <sge/opengl/egl/visual/create.hpp>
#include <sge/renderer/parameters/vsync.hpp>
#include <sge/renderer/pixel_format/object_fwd.hpp>
#include <awl/system/object_fwd.hpp>
#include <awl/visual/object.hpp>
#include <awl/visual/object_unique_ptr.hpp>
#include <awl/window/object.hpp>
#include <fcppt/make_unique_ptr.hpp>


sge::opengl::egl::system::system()
:
	sge::opengl::device_state::system()
{
}

sge::opengl::egl::system::~system()
{
}

awl::visual::object_unique_ptr
sge::opengl::egl::system::create_visual(
	awl::system::object &_awl_system,
	sge::renderer::pixel_format::object const &_pixel_format
)
{
	return
		sge::opengl::egl::visual::create(
			_awl_system,
			_pixel_format
		);
}

sge::opengl::device_state::context_unique_ptr
sge::opengl::egl::system::create_context(
	awl::window::object &_window
)
{
	return
		fcppt::make_unique_ptr<
			sge::opengl::egl::context
		>(
			sge::opengl::egl::create_native_display(
				_window
			),
			sge::opengl::egl::native_window(
				_window
			),
			_window.visual()
		);
}

void
sge::opengl::egl::system::vsync(
	sge::opengl::device_state::scoped_current const &,
	awl::window::object &,
	sge::renderer::parameters::vsync
)
{
}
