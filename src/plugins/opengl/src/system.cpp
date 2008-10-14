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


#include <sge/config.h>
#include "../system.hpp"
#include "../device.hpp"
#if defined(SGE_HAVE_X11)
#include "../glx/choose_visual.hpp"
#include "../glx/create_visual.hpp"
#include <sge/x11/colormap.hpp>
#include <sge/x11/visual.hpp>
#include <sge/x11/display.hpp>
#include <sge/x11/window.hpp>
#elif defined(SGE_WINDOWS_PLATFORM)
#include <sge/windows/gdi_device.hpp>
#include <sge/windows/window.hpp>
#include <sge/windows/choose_and_set_pixel_format.hpp>
#else
#error "Implement me!"
#endif
#include <sge/renderer/caps.hpp>
#include <sge/renderer/parameters.hpp>
#include <sge/exception.hpp>
#include <sge/text.hpp>
#include <sge/string.hpp>
#include <sge/raw_vector_impl.hpp>

sge::renderer::device_ptr const
sge::ogl::system::create_renderer(
	renderer::parameters const &param,
	renderer::adapter_type const adapter,
	window_ptr const wnd)
{
	if(ref.lock())
		throw exception(
			SGE_TEXT("The opengl plugin may only have one renderer!"));

	renderer::device_ptr const r(
		new device(
			param,
			adapter,
			wnd));
	ref = r.get_boost_ptr();
	return r;
}

sge::window_ptr const
sge::ogl::system::create_window(
	renderer::parameters const &param)
{
	string const default_title(
		SGE_TEXT("spacegameengine - untitled"));
#if defined(SGE_HAVE_X11)
	x11::display_ptr const dsp(
		new x11::display());

	x11::visual_ptr const visual(
	glx::create_visual(
		dsp,
		dsp->default_screen(),
		glx::choose_visual(
			param.mode().depth,
			param.dbuffer(),
			param.sbuffer()).data()));
	
	x11::colormap_ptr const colormap(
		new x11::colormap(
			dsp,
			visual->info()));

	return window_ptr(
		new x11::window(
			window::window_pos(0,0),
			param.mode().size,
			default_title,
			dsp,
			param.wmode() == renderer::window_mode::fullscreen,
			visual,
			colormap));
#elif defined(SGE_WINDOWS_PLATFORM)
	windows::window_ptr const wnd(
		new windows::window(
			param.mode().size,
			default_title));

	windows::choose_and_set_pixel_format(
		windows::gdi_device(
			wnd->hwnd(),
			windows::gdi_device::get_tag()),
		PFD_DRAW_TO_WINDOW |
		PFD_SUPPORT_OPENGL |
		PFD_DOUBLEBUFFER,
		PFD_TYPE_RGBA,
		static_cast<BYTE>(param.mode().depth),
		static_cast<BYTE>(param.dbuffer()),
		static_cast<BYTE>(param.sbuffer()));

	return wnd;
#else
#error "Implement me!"
#endif
}

sge::renderer::caps_array const
sge::ogl::system::caps() const
{
	renderer::caps_array v;
	return v; // FIXME
}
