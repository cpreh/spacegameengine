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


#include "../choose_resolution.hpp"
#include "../configuration.hpp"
#include "../resolution.hpp"
#include "../mode.hpp"
#include "../current_resolution.hpp"
#include "../check_extension.hpp"
#include <sge/renderer/display_mode.hpp>
#include <sge/renderer/screen_unit.hpp>
#include <sge/x11/window.hpp>
#include <sge/exception.hpp>
#include <fcppt/make_shared_ptr.hpp>
#include <fcppt/text.hpp>

sge::opengl::xrandr::resolution_ptr const
sge::opengl::xrandr::choose_resolution(
	x11::window_ptr const wnd,
	renderer::display_mode const &mode
)
{
	check_extension(
		wnd->display()
	);

	configuration_ptr const config(
		fcppt::make_shared_ptr<
			configuration
		>(
			wnd
		)
	);

	int nsizes;
	XRRScreenSize *const sizes(
		XRRConfigSizes(
			config->get(),
			&nsizes
		)
	);

	for(int i = 0; i < nsizes; ++i)
		if(
			static_cast<renderer::screen_unit>(sizes[i].width) == mode.size().w()
			&& static_cast<renderer::screen_unit>(sizes[i].height) == mode.size().h()
		)
			return resolution_ptr(
				fcppt::make_shared_ptr<
					resolution
				>(
					wnd,
					config,
					xrandr::mode(
						i,
						RR_Rotate_0,
						mode.refresh_rate()
					),
					current_resolution(
						config
					)
				)
			);

	throw exception(
		FCPPT_TEXT("No matching resolution found!")
	);
}
