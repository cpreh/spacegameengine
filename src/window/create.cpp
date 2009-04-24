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



#include <sge/window/create.hpp>
#include <sge/config.h>
#if defined(SGE_WINDOWS_PLATFORM)
#include <sge/windows/create_window.hpp>
#include <sge/optional.hpp>
#elif defined(SGE_HAVE_X11)
#include <sge/x11/create_window.hpp>
#include <sge/x11/display.hpp>
#include <sge/x11/visual.hpp>
#include <sge/x11/screen.hpp>
#include <sge/window/parameters.hpp>
#endif

sge::window::instance_ptr const
sge::window::create(
	parameters const &param)
{
#if defined(SGE_WINDOWS_PLATFORM)
	return windows::create_window(
		param,
		windows::optional_renderer_parameters());
#elif defined(SGE_HAVE_X11)
	x11::display_ptr const dsp(
		new x11::display());

	int const screen(
		default_screen(
			dsp));

	x11::visual_ptr const visual(
		new x11::visual(
			dsp,
			screen));
			
	return x11::create_window(
		param,
		dsp,
		screen,
		32,//param.param().mode().bit_depth(), FIXME
		visual,
		false);

#else
#error "Implement me!"
#endif
}
