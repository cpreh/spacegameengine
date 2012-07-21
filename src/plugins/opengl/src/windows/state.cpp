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
#include <sge/opengl/windows/change_display_settings.hpp>
#include <sge/opengl/windows/state.hpp>
#include <sge/renderer/exception.hpp>
#include <sge/renderer/parameters/object.hpp>
#include <awl/backends/windows/windows.hpp>
#include <fcppt/text.hpp>


sge::opengl::windows::state::state(
	sge::opengl::context::system::object &,
	sge::renderer::parameters::object const &_parameters,
	awl::backends::windows::window::object &_window
)
:
	context_(
		_window
	),
	scoped_current_(
		context_
	)
{
	if(
		_parameters.display_mode()
	)
		sge::opengl::windows::change_display_settings(
			*_parameters.display_mode()
		);
}

sge::opengl::windows::state::~state()
{
}

void
sge::opengl::windows::state::begin_rendering()
{
}

void
sge::opengl::windows::state::swap_buffers()
{
	if(
		::wglSwapLayerBuffers(
			context_.dc().hdc(),
			WGL_SWAP_MAIN_PLANE
		)
		== FALSE
	)
		throw sge::renderer::exception(
			FCPPT_TEXT("wglSwapLayerBuffers() failed!")
		);
}
