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


#include <sge/opengl/xrandr/make_display_mode.hpp>
#include <sge/opengl/xrandr/refresh_rate.hpp>
#include <sge/renderer/screen_size.hpp>
#include <sge/renderer/display_mode/dimensions.hpp>
#include <sge/renderer/display_mode/object.hpp>
#include <sge/renderer/display_mode/optional_dimensions.hpp>
#include <sge/renderer/display_mode/optional_refresh_rate.hpp>
#include <sge/renderer/display_mode/pixel_size.hpp>
#include <sge/renderer/display_mode/refresh_rate.hpp>
#include <fcppt/cast/to_unsigned.hpp>
#include <fcppt/config/external_begin.hpp>
#include <X11/extensions/Xrandr.h>
#include <fcppt/config/external_end.hpp>


sge::renderer::display_mode::object
sge::opengl::xrandr::make_display_mode(
	XRRScreenSize const &_screen_size,
	sge::opengl::xrandr::refresh_rate const _refresh_rate
)
{
	return
		sge::renderer::display_mode::object{
			sge::renderer::display_mode::pixel_size{
				sge::renderer::screen_size{
					fcppt::cast::to_unsigned(
						_screen_size.width
					),
					fcppt::cast::to_unsigned(
						_screen_size.height
					)
				}
			},
			sge::renderer::display_mode::optional_dimensions{
				sge::renderer::display_mode::dimensions{
					sge::renderer::screen_size{
						fcppt::cast::to_unsigned(
							_screen_size.mwidth
						),
						fcppt::cast::to_unsigned(
							_screen_size.mheight
						)
					}
				}
			},
			sge::renderer::display_mode::optional_refresh_rate{
				sge::renderer::display_mode::refresh_rate{
					fcppt::cast::to_unsigned(
						_refresh_rate.get()
					)
				}
			}
		};

}
