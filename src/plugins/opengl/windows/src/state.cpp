/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2007  Carl Philipp Reh (sefi@s-e-f-i.de)

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


#include "../state.hpp"
#include "../change_display_mode.hpp"
#include <sge/renderer/parameters.hpp>
#include <sge/exception.hpp>
#include <sge/text.hpp>
#include <sge/windows/window.hpp>
#include <sge/windows/windows.hpp>

sge::ogl::windows::state::state(
	renderer::parameters const &param,
	renderer::adapter_type const adapter,
	window::instance_ptr const wnd_,
	view_port_fun const &)
:
	wnd(
		polymorphic_pointer_cast<sge::windows::window>(
			wnd_)),
	hdc(
		wnd->hwnd(),
		windows::gdi_device::get_tag()),
	context(
		wgl::context(
			*hdc)),
	current(
		wgl::current(
			*hdc,
			*context))
{

	if(!windowed)
		change_display_settings(
			param.mode());	
}

void sge::ogl::windows::state::swap_buffers()
{
	if(wglSwapLayerBuffers(hdc.hdc(), WGL_SWAP_MAIN_PLANE) == FALSE)
		throw exception(
			SGE_TEXT("wglSwapLayerBuffers() failed!"));
}
