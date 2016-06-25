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
#include <sge/opengl/backend/current.hpp>
#include <sge/opengl/backend/current_unique_ptr.hpp>
#include <sge/opengl/glx/context.hpp>
#include <sge/opengl/glx/current.hpp>
#include <sge/opengl/glx/make_current.hpp>
#include <sge/opengl/glx/optional_proc_address_function.hpp>
#include <sge/renderer/exception.hpp>
#include <awl/backends/x11/display.hpp>
#include <awl/backends/x11/visual/object.hpp>
#include <awl/backends/x11/window/object.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/text.hpp>
#include <fcppt/unique_ptr_to_base.hpp>
#include <fcppt/config/external_begin.hpp>
#include <GL/glx.h>
#include <X11/X.h>
#include <X11/Xutil.h>
#include <fcppt/config/external_end.hpp>


sge::opengl::glx::context::context(
	awl::backends::x11::window::object &_window,
	sge::opengl::glx::optional_proc_address_function const _proc_address
)
:
	sge::opengl::backend::context(),
	window_(
		_window
	),
	proc_address_(
		_proc_address
	),
	context_(
		::glXCreateContext(
			_window.display().get(),
			const_cast<
				XVisualInfo *
			>(
				window_.x11_visual().info()
			),
			nullptr,
			True
		)
	)
{
	if(
		context_
		==
		nullptr
	)
		throw sge::renderer::exception(
			FCPPT_TEXT("glXCreateContext() failed!")
		);
}

sge::opengl::glx::context::~context()
{
	::glXDestroyContext(
		window_.display().get(),
		context_
	);
}

sge::opengl::backend::current_unique_ptr
sge::opengl::glx::context::activate()
{
	sge::opengl::glx::make_current(
		window_.display().get(),
		window_.get(),
		context_
	);

	return
		fcppt::unique_ptr_to_base<
			sge::opengl::backend::current
		>(
			fcppt::make_unique_ptr<
				sge::opengl::glx::current
			>(
				window_,
				proc_address_
			)
		);
}

void
sge::opengl::glx::context::deactivate(
	sge::opengl::backend::current_unique_ptr &&
)
{
	sge::opengl::glx::make_current(
		window_.display().get(),
		None,
		nullptr
	);
}
