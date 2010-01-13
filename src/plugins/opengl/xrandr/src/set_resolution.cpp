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


#include "../set_resolution.hpp"
#include "../mode.hpp"
#include "../configuration.hpp"
#include <sge/x11/window.hpp>
#include <sge/x11/display.hpp>
#include <sge/renderer/refresh_rate_dont_care.hpp>
#include <sge/renderer/exception.hpp>
#include <fcppt/text.hpp>
#include <X11/Xlib.h>
#include <X11/extensions/Xrandr.h>

void
sge::opengl::xrandr::set_resolution(
	sge::x11::window_ptr const wnd,
	configuration_ptr const config,
	mode const &m
)
{
	if(m.rate() != renderer::refresh_rate_dont_care)
	{
		if(
			XRRSetScreenConfigAndRate(
				wnd->display()->get(),
				config->get(),
				wnd->get(),
				m.index(),
				m.rotation(),
				static_cast<short>(m.rate()),
				CurrentTime
			) != Success
		)
			throw sge::renderer::exception(
				FCPPT_TEXT("Cannot change screen mode with rate!")
			);
	}
	else
	{
		if(
			XRRSetScreenConfig(
				wnd->display()->get(),
				config->get(),
				wnd->get(),
				m.index(),
				m.rotation(),
				CurrentTime
			) != Success
		)
			throw sge::renderer::exception(
				FCPPT_TEXT("Cannot change screen mode!")
			);
	}
}
