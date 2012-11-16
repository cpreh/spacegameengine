/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2012 Carl Philipp Reh (sefi@s-e-f-i.de)

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




#include <sge/opengl/context/system/object_fwd.hpp>
#include <sge/opengl/device_state/context_unique_ptr.hpp>
#include <sge/opengl/device_state/scoped_current_fwd.hpp>
#include <sge/opengl/device_state/system.hpp>
#include <sge/opengl/wgl/context.hpp>
#include <sge/opengl/wgl/system.hpp>
#include <sge/opengl/windows/visual/create.hpp>
#include <sge/renderer/parameters/vsync.hpp>
#include <sge/renderer/pixel_format/object_fwd.hpp>
#include <awl/backends/windows/window/object.hpp>
#include <awl/system/object_fwd.hpp>
#include <awl/visual/object.hpp>
#include <awl/visual/object_unique_ptr.hpp>
#include <awl/window/object_fwd.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/ref.hpp>


sge::opengl::wgl::system::system(
	sge::opengl::context::system::object &_system_context
)
:
	sge::opengl::device_state::system(),
	system_context_(
		_system_context
	)
{
}

sge::opengl::wgl::system::~system()
{
}

awl::visual::object_unique_ptr
sge::opengl::wgl::system::create_visual(
	awl::system::object &,
	sge::renderer::pixel_format::object const &_pixel_format
)
{
	// TODO:!
	return
		sge::opengl::windows::visual::create(
			system_context_,
			_pixel_format
		);
}

sge::opengl::device_state::context_unique_ptr
sge::opengl::wgl::system::create_context(
	awl::window::object &_window
)
{
	return
		fcppt::make_unique_ptr<
			sge::opengl::wgl::context
		>(
			fcppt::ref(
				dynamic_cast<
					awl::backends::windows::window::object &
				>(
					_window
				)
			)
		);
}

void
sge::opengl::wgl::system::vsync(
	sge::opengl::device_state::scoped_current const &,
	awl::window::object &_window,
	sge::renderer::parameters::vsync::type const _vsync
)
{
}
