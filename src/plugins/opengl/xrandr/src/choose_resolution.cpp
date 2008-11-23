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


#include "../choose_resolution.hpp"
#include "../configuration.hpp"
#include "../resolution.hpp"
#include "../mode.hpp"
#include <sge/renderer/display_mode.hpp>
#include <sge/x11/window.hpp>
#include <sge/x11/display.hpp>
#include <sge/make_shared_ptr.hpp>
#include <sge/exception.hpp>
#include <sge/text.hpp>

sge::ogl::xrandr::resolution_ptr const
sge::ogl::xrandr::choose_resolution(
	x11::window_ptr const wnd,
	renderer::display_mode const &mode)
{
	{
		int event_base_return,
		    error_base_return;
		
		if(XRRQueryExtension(
			wnd->display()->get(),
			&event_base_return,
			&error_base_return)
		== False)
			throw exception(
				SGE_TEXT("xrandr extension not present!"));
	}

	configuration_ptr const config(
		make_shared_ptr<configuration>(
			wnd));
	
	int nsizes;
	XRRScreenSize *const sizes
		= XRRConfigSizes(
			config->get(),
			&nsizes);
	
	if(nsizes == 0)
		throw exception(
			SGE_TEXT("XRRConfigSizes() failed!"));
	int cur_size;
	Rotation cur_rotation;
	cur_size = XRRConfigCurrentConfiguration(
		config->get(),
		&cur_rotation);
	
	short const rate = XRRConfigCurrentRate(
		config->get());

	// TODO: how do we check for errors here?
	
	for(int i = 0; i < nsizes; ++i)
		if(static_cast<renderer::screen_unit>(sizes[i].width) == mode.size().w()
		&& static_cast<renderer::screen_unit>(sizes[i].height) == mode.size().h())
			return resolution_ptr(
				make_shared_ptr<resolution>(
					wnd,
					config,
					xrandr::mode(
						i,
						RR_Rotate_0,
						mode.refresh_rate()),
					xrandr::mode(
						cur_size,
						cur_rotation,
						rate)));
	throw exception(
		SGE_TEXT("No matching resolution found!"));
}
