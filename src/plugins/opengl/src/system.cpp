/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2009 Carl Philipp Reh (sefi@s-e-f-i.de)

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
#include "../glx/visual.hpp"
#include <sge/x11/visual.hpp>
#include <sge/x11/display.hpp>
#include <sge/x11/create_window.hpp>
#include <sge/x11/screen.hpp>
#include <sge/renderer/parameters.hpp>
#elif defined(SGE_WINDOWS_PLATFORM)
#include <sge/windows/create_window.hpp>
#else
#error "Implement me!"
#endif
#include <sge/renderer/caps.hpp>
#include <sge/window/parameters.hpp>
#include <sge/exception.hpp>
#include <sge/text.hpp>
#include <sge/container/raw_vector_impl.hpp>

sge::renderer::device_ptr const
sge::ogl::system::create_renderer(
	renderer::parameters const &param,
	renderer::adapter_type const adapter,
	window::instance_ptr const wnd)
{
	if(ref.lock())
		throw exception(
			SGE_TEXT("The opengl plugin may only have one renderer!"));

	renderer::device_ptr const r(
		new device(
			param,
			adapter,
			wnd));
	ref = r;
	return r;
}

sge::window::instance_ptr const
sge::ogl::system::create_window(
	window::parameters const &param,
	renderer::parameters const &rparam)
{
#if defined(SGE_HAVE_X11)
	sge::x11::display_ptr const dsp(
		new sge::x11::display());

	glx::visual_ptr const visual(
		glx::create_visual(
			dsp,
			sge::x11::default_screen(dsp),
			glx::choose_visual(
				rparam.mode().bit_depth(),
				rparam.dbuffer(),
				rparam.sbuffer()).data()));
	
	return sge::x11::create_window(
		param,
		dsp,
		visual->info().screen,
		visual->info().depth,
		visual,
		rparam.wmode() == renderer::window_mode::fullscreen);
#elif defined(SGE_WINDOWS_PLATFORM)
	return sge::windows::create_window(
		param,
		rparam);
#else
#error "Implement me!"
#endif
}
