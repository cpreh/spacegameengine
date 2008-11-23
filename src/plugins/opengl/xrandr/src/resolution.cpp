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


#include "../resolution.hpp"
#include "../configuration.hpp"
#include <sge/x11/window.hpp>
#include <sge/x11/display.hpp>
#include <X11/Xlib.h>
#include <X11/extensions/Xrandr.h>

sge::ogl::xrandr::resolution::resolution(
	sge::x11::window_ptr const wnd,
	configuration_ptr const config,
	mode const &new_mode,
	mode const &old_mode)
:
	wnd(wnd),
	config(config),
	old_mode(old_mode)
{
	XRRSetScreenConfigAndRate(
		wnd->display()->get(),
		config->get(),
		wnd->get(),
		new_mode.index(),
		new_mode.rotation(),
		static_cast<short>(new_mode.rate()),
		CurrentTime);
}

sge::ogl::xrandr::resolution::~resolution()
{
	XRRSetScreenConfigAndRate(
		wnd->display()->get(),
		config->get(),
		wnd->get(),
		old_mode.index(),
		old_mode.rotation(),
		static_cast<short>(old_mode.rate()),
		CurrentTime);
}
