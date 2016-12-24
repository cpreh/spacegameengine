/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2016 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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
#include <sge/opengl/xrandr/current_mode.hpp>
#include <sge/opengl/xrandr/mode.hpp>
#include <sge/opengl/xrandr/mode_index.hpp>
#include <sge/opengl/xrandr/refresh_rate.hpp>
#include <sge/opengl/xrandr/rotation.hpp>
#include <fcppt/config/external_begin.hpp>
#include <X11/extensions/Xrandr.h>
#include <fcppt/config/external_end.hpp>


sge::opengl::xrandr::mode
sge::opengl::xrandr::current_mode(
	sge::opengl::xrandr::configuration const &_config
)
{
	Rotation cur_rotation;

	SizeID const cur_size(
		::XRRConfigCurrentConfiguration(
			_config.get(),
			&cur_rotation
		)
	);

	short const rate(
		::XRRConfigCurrentRate(
			_config.get()
		)
	);

	return
		sge::opengl::xrandr::mode(
			sge::opengl::xrandr::mode_index{
				static_cast<
					int
				>(
					cur_size
				)
			},
			sge::opengl::xrandr::rotation{
				cur_rotation
			},
			sge::opengl::xrandr::refresh_rate{
				rate
			}
		);
}
