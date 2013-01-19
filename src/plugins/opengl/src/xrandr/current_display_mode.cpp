/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2013 Carl Philipp Reh (sefi@s-e-f-i.de)

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
#include <sge/opengl/xrandr/current_display_mode.hpp>
#include <sge/opengl/xrandr/current_mode.hpp>
#include <sge/opengl/xrandr/mode.hpp>
#include <sge/renderer/screen_size.hpp>
#include <sge/renderer/screen_unit.hpp>
#include <sge/renderer/display_mode/dimensions.hpp>
#include <sge/renderer/display_mode/object.hpp>
#include <sge/renderer/display_mode/optional_dimensions.hpp>
#include <sge/renderer/display_mode/pixel_size.hpp>
#include <fcppt/config/external_begin.hpp>
#include <X11/extensions/Xrandr.h>
#include <fcppt/config/external_end.hpp>


sge::renderer::display_mode::object const
sge::opengl::xrandr::current_display_mode(
	sge::opengl::xrandr::configuration const &_config
)
{
	sge::opengl::xrandr::mode const mode(
		sge::opengl::xrandr::current_mode(
			_config
		)
	);

	int nsizes;

	::XRRScreenSize *const sizes(
		::XRRConfigSizes(
			_config.get(),
			&nsizes
		)
	);

	::XRRScreenSize const &cur(
		sizes[
			mode.index()
		]
	);

	return
		sge::renderer::display_mode::object(
			sge::renderer::display_mode::pixel_size(
				sge::renderer::screen_size(
					static_cast<
						sge::renderer::screen_unit
					>(
						cur.width
					),
					static_cast<
						sge::renderer::screen_unit
					>(
						cur.height
					)
				)
			),
			sge::renderer::display_mode::optional_dimensions(
				sge::renderer::display_mode::dimensions(
					sge::renderer::screen_size(
						static_cast<
							sge::renderer::screen_unit
						>(
							cur.mwidth
						),
						static_cast<
							sge::renderer::screen_unit
						>(
							cur.mheight
						)
					)
				)
			),
			mode.rate()
		);
}
