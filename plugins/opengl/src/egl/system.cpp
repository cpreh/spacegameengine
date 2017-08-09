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
#include <sge/opengl/egl/bind_api.hpp>
#include <sge/opengl/egl/context.hpp>
#include <sge/opengl/egl/create_display.hpp>
#include <sge/opengl/egl/display.hpp>
#include <sge/opengl/egl/surface.hpp>
#include <sge/opengl/egl/system.hpp>
#include <sge/opengl/egl/version_output.hpp>
#include <sge/opengl/egl/visual/to_config.hpp>
#include <sge/renderer/pixel_format/object_fwd.hpp>
#include <sge/window/object.hpp>
#include <awl/system/object_fwd.hpp>
#include <awl/visual/object.hpp>
#include <awl/visual/object_unique_ptr.hpp>
#include <awl/window/object.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/text.hpp>
#include <fcppt/unique_ptr_to_base.hpp>
#include <fcppt/log/_.hpp>
#include <fcppt/log/info.hpp>
#include <fcppt/log/object_fwd.hpp>


sge::opengl::egl::system::system(
	fcppt::log::object &_log,
	awl::system::object &_awl_system
)
:
	sge::opengl::backend::system(),
	log_{
		_log
	},
	awl_system_(
		_awl_system
	),
	egl_display_(
		sge::opengl::egl::create_display(
			_log,
			_awl_system
		)
	),
	init_(
		egl_display_->get()
	)
{
	FCPPT_LOG_INFO(
		_log,
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
		egl_display_->create_visual(
			init_,
			_pixel_format
		);
}

sge::opengl::backend::context_unique_ptr
sge::opengl::egl::system::create_context(
	sge::window::object &_window
)
{
	EGLConfig const config{
		sge::opengl::egl::visual::to_config(
			log_,
			egl_display_->get(),
			_window.awl_object().visual()
		)
	};

	return
		fcppt::unique_ptr_to_base<
			sge::opengl::backend::context
		>(
			fcppt::make_unique_ptr<
				sge::opengl::egl::context
			>(
				egl_display_->get(),
				config,
				egl_display_->create_surface(
					config,
					_window
				)
			)
		);
}
