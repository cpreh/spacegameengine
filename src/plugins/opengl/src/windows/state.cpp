/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2011 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#include <sge/opengl/windows/state.hpp>
#include <sge/opengl/windows/change_display_settings.hpp>
#include <sge/renderer/display_mode.hpp>
#include <sge/renderer/exception.hpp>
#include <sge/renderer/parameters.hpp>
#include <awl/backends/windows/windows.hpp>
#include <awl/backends/windows/window/instance.hpp>
#include <fcppt/text.hpp>
#include <fcppt/variant/holds_type.hpp>
#include <fcppt/variant/object_impl.hpp>


sge::opengl::windows::state::state(
	opengl::context::object &,
	renderer::parameters const &_param,
	renderer::adapter const _adapter,
	awl::backends::windows::window::instance &_window
)
:
	window_(
		_window
	),
	hdc_(
		window_.hwnd(),
		awl::backends::windows::gdi_device::get_tag()
	),
	context_(
		hdc_
	),
	current_(
		hdc_,
		context_
	)
{
	if(
		fcppt::variant::holds_type<
			sge::renderer::display_mode
		>(
			_param.screen_mode()
		)
	)
		windows::change_display_settings(
			_param.screen_mode().get<
				sge::renderer::display_mode
			>()
		);
}

sge::opengl::windows::state::~state()
{
}

void
sge::opengl::windows::state::swap_buffers()
{
	if(
		::wglSwapLayerBuffers(
			hdc_.hdc(),
			WGL_SWAP_MAIN_PLANE
		)
		== FALSE
	)
		throw sge::renderer::exception(
			FCPPT_TEXT("wglSwapLayerBuffers() failed!")
		);
}
