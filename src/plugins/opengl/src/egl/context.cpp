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


#include <sge/opengl/egl/context.hpp>
#include <sge/opengl/egl/get_display.hpp>
#include <sge/opengl/egl/native_display.hpp>
#include <sge/opengl/egl/native_display_unique_ptr.hpp>
#include <sge/opengl/egl/swap_buffers.hpp>
#include <sge/opengl/egl/visual/choose_config.hpp>
#include <awl/visual/object_fwd.hpp>
#include <fcppt/config/external_begin.hpp>
#include <EGL/egl.h>
#include <utility>
#include <fcppt/config/external_end.hpp>


sge::opengl::egl::context::context(
	sge::opengl::egl::native_display_unique_ptr &&_native_display,
	EGLNativeWindowType const _window,
	awl::visual::object const &_visual
)
:
	native_display_(
		std::move(
			_native_display
		)
	),
	display_(
		sge::opengl::egl::get_display(
			native_display_->get()
		)
	),
	init_(
		display_
	),
	config_(
		sge::opengl::egl::visual::choose_config(
			display_,
			_visual
		)
	),
	surface_(
		display_,
		config_,
		_window
	),
	context_(
		display_,
		config_
	)
{
}

sge::opengl::egl::context::~context()
{
}

void
sge::opengl::egl::context::activate()
{
	context_.activate(
		surface_.get()
	);
}

void
sge::opengl::egl::context::deactivate()
{
	context_.deactivate();
}

void
sge::opengl::egl::context::begin_rendering()
{
}

void
sge::opengl::egl::context::end_rendering()
{
	sge::opengl::egl::swap_buffers(
		display_,
		surface_.get()
	);
}
