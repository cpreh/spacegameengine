/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2014 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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


#include <sge/opengl/logger.hpp>
#include <sge/opengl/backend/context_unique_ptr.hpp>
#include <sge/opengl/backend/scoped_current_fwd.hpp>
#include <sge/opengl/backend/system.hpp>
#include <sge/opengl/egl/bind_api.hpp>
#include <sge/opengl/egl/context.hpp>
#include <sge/opengl/egl/create_native_display.hpp>
#include <sge/opengl/egl/get_display.hpp>
#include <sge/opengl/egl/native_display.hpp>
#include <sge/opengl/egl/native_window.hpp>
#include <sge/opengl/egl/system.hpp>
#include <sge/opengl/egl/version_output.hpp>
#include <sge/opengl/egl/visual/create.hpp>
#include <sge/renderer/display_mode/vsync.hpp>
#include <sge/renderer/pixel_format/object_fwd.hpp>
#include <awl/system/object_fwd.hpp>
#include <awl/visual/object.hpp>
#include <awl/visual/object_unique_ptr.hpp>
#include <awl/window/object.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/text.hpp>
#include <fcppt/log/_.hpp>
#include <fcppt/log/info.hpp>


sge::opengl::egl::system::system(
	awl::system::object &_awl_system
)
:
	sge::opengl::backend::system(),
	awl_system_(
		_awl_system
	),
	egl_native_display_(
		sge::opengl::egl::create_native_display(
			_awl_system
		)
	),
	egl_display_(
		sge::opengl::egl::get_display(
			egl_native_display_->get()
		)
	),
	init_(
		egl_display_
	)
{
	FCPPT_LOG_INFO(
		sge::opengl::logger(),
		fcppt::log::_
			<< FCPPT_TEXT("EGL version is ")
			<< init_.version()
	);

	sge::opengl::egl::bind_api(
		EGL_OPENGL_API
	);
}

sge::opengl::egl::system::~system()
{
}

awl::visual::object_unique_ptr
sge::opengl::egl::system::create_visual(
	sge::renderer::pixel_format::object const &_pixel_format
)
{
	return
		sge::opengl::egl::visual::create(
			init_,
			awl_system_,
			egl_display_,
			_pixel_format
		);
}

sge::opengl::backend::context_unique_ptr
sge::opengl::egl::system::create_context(
	awl::window::object &_window
)
{
	return
		fcppt::make_unique_ptr<
			sge::opengl::egl::context
		>(
			egl_display_,
			sge::opengl::egl::native_window(
				_window
			),
			_window.visual()
		);
}

void
sge::opengl::egl::system::vsync(
	sge::opengl::backend::scoped_current const &,
	awl::window::object &,
	sge::renderer::display_mode::vsync const _vsync
)
{
	// TODO
}
