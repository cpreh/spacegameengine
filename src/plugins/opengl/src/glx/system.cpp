/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2015 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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


#include <sge/opengl/backend/context.hpp>
#include <sge/opengl/backend/context_unique_ptr.hpp>
#include <sge/opengl/backend/scoped_current_fwd.hpp>
#include <sge/opengl/backend/system.hpp>
#include <sge/opengl/context/system/object_fwd.hpp>
#include <sge/opengl/glx/context.hpp>
#include <sge/opengl/glx/system.hpp>
#include <sge/opengl/glx/vsync.hpp>
#include <sge/opengl/glx/visual/create.hpp>
#include <sge/renderer/display_mode/vsync.hpp>
#include <sge/renderer/pixel_format/object_fwd.hpp>
#include <awl/backends/x11/system/object.hpp>
#include <awl/backends/x11/window/object.hpp>
#include <awl/visual/object.hpp>
#include <awl/visual/object_unique_ptr.hpp>
#include <awl/window/object_fwd.hpp>
#include <fcppt/make_unique_ptr_fcppt.hpp>
#include <fcppt/unique_ptr_to_base.hpp>
#include <fcppt/cast/static_downcast.hpp>


sge::opengl::glx::system::system(
	sge::opengl::context::system::object &_system_context,
	awl::backends::x11::system::object &_awl_system
)
:
	system_context_(
		_system_context
	),
	awl_system_(
		_awl_system
	)
{
}

sge::opengl::glx::system::~system()
{
}

awl::visual::object_unique_ptr
sge::opengl::glx::system::create_visual(
	sge::renderer::pixel_format::object const &_pixel_format
)
{
	return
		sge::opengl::glx::visual::create(
			system_context_,
			awl_system_,
			_pixel_format
		);
}

sge::opengl::backend::context_unique_ptr
sge::opengl::glx::system::create_context(
	awl::window::object &_window
)
{
	return
		fcppt::unique_ptr_to_base<
			sge::opengl::backend::context
		>(
			fcppt::make_unique_ptr_fcppt<
				sge::opengl::glx::context
			>(
				fcppt::cast::static_downcast<
					awl::backends::x11::window::object &
				>(
					_window
				)
			)
		);
}

void
sge::opengl::glx::system::vsync(
	sge::opengl::backend::scoped_current const &,
	awl::window::object &_awl_window,
	sge::renderer::display_mode::vsync const _vsync
)
{
	if(
		_vsync
		==
		sge::renderer::display_mode::vsync::on
	)
		sge::opengl::glx::vsync(
			system_context_,
			fcppt::cast::static_downcast<
				awl::backends::x11::window::object &
			>(
				_awl_window
			).display()
		);
}
