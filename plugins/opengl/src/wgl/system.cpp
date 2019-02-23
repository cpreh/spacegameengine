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


#include <sge/opengl/backend/context.hpp>
#include <sge/opengl/backend/context_unique_ptr.hpp>
#include <sge/opengl/backend/system.hpp>
#include <sge/opengl/wgl/context.hpp>
#include <sge/opengl/wgl/get_config.hpp>
#include <sge/opengl/wgl/system.hpp>
#include <sge/opengl/windows/visual/create.hpp>
#include <sge/renderer/pixel_format/object_fwd.hpp>
#include <sge/window/object.hpp>
#include <awl/backends/windows/window/object.hpp>
#include <awl/system/object_fwd.hpp>
#include <awl/visual/object.hpp>
#include <awl/visual/object_unique_ptr.hpp>
#include <awl/window/object.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/unique_ptr_to_base.hpp>
#include <fcppt/cast/dynamic_exn.hpp>


sge::opengl::wgl::system::system(
	awl::system::object &_awl_system
)
:
	sge::opengl::backend::system(),
	config_(
		sge::opengl::wgl::get_config(
			_awl_system
		)
	)
{
}

sge::opengl::wgl::system::~system()
{
}

awl::visual::object_unique_ptr
sge::opengl::wgl::system::create_visual(
	sge::renderer::pixel_format::object const &_pixel_format
)
{
	return
		sge::opengl::windows::visual::create(
			config_.visual_config(),
			_pixel_format
		);
}

sge::opengl::backend::context_unique_ptr
sge::opengl::wgl::system::create_context(
	sge::window::object &_window
)
{
	return
		fcppt::unique_ptr_to_base<
			sge::opengl::backend::context
		>(
			fcppt::make_unique_ptr<
				sge::opengl::wgl::context
			>(
				fcppt::cast::dynamic_exn<
					awl::backends::windows::window::object &
				>(
					_window.awl_object()
				)
			)
		);
}


