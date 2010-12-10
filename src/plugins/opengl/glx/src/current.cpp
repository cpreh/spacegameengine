/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2010 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#include <GL/glx.h>
#include "../current.hpp"
#include "../context.hpp"
#include <sge/renderer/exception.hpp>
#include <fcppt/text.hpp>
#include <awl/backends/x11/window/instance.hpp>
#include <awl/backends/x11/display.hpp>

sge::opengl::glx::current::current(
	awl::backends::x11::display_ptr const _display,
	awl::backends::x11::window::instance_ptr const _window,
	context_ptr const _context
)
:
	display_(_display),
	context_(_context)
{
	if(
		::glXMakeCurrent(
			_display->get(),
			_window->get(),
			_context->get()
		)
		== false
	)
		throw sge::renderer::exception(
			FCPPT_TEXT("glXMakeCurrent() failed!")
		);
}

sge::opengl::glx::current::~current()
{
	::glXMakeCurrent(
		display_->get(),
		None,
		NULL
	);
}
