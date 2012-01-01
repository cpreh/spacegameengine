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


#include <sge/opengl/xrandr/configuration.hpp>
#include <sge/opengl/xrandr/current_resolution.hpp>
#include <sge/opengl/xrandr/mode.hpp>
#include <fcppt/config/external_begin.hpp>
#include <X11/Xlib.h>
#include <X11/extensions/Xrandr.h>
#include <fcppt/config/external_end.hpp>


sge::opengl::xrandr::mode const
sge::opengl::xrandr::current_resolution(
	configuration_ptr const config
)
{
	Rotation cur_rotation;

	int const cur_size(
		XRRConfigCurrentConfiguration(
			config->get(),
			&cur_rotation
		)
	);

	short const rate(
		XRRConfigCurrentRate(
			config->get()
		)
	);

	return mode(
		cur_size,
		cur_rotation,
		sge::renderer::refresh_rate(
			rate
		)
	);
}
