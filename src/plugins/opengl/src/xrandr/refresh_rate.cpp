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


#include <sge/opengl/xrandr/combine_rates.hpp>
#include <sge/opengl/xrandr/crtc_info.hpp>
#include <sge/opengl/xrandr/crtcs_view.hpp>
#include <sge/opengl/xrandr/modes_view.hpp>
#include <sge/opengl/xrandr/refresh_rate.hpp>
#include <sge/opengl/xrandr/refresh_rate_from_mode.hpp>
#include <sge/opengl/xrandr/screen_resources.hpp>
#include <sge/renderer/display_mode/optional_refresh_rate.hpp>
#include <awl/backends/x11/display_fwd.hpp>
#include <awl/backends/x11/window/object.hpp>
#include <awl/window/rect.hpp>
#include <fcppt/math/box/intersects.hpp>


sge::renderer::display_mode::optional_refresh_rate const
sge::opengl::xrandr::refresh_rate(
	awl::backends::x11::display &_display,
	awl::backends::x11::window::object &_window
)
{
	sge::opengl::xrandr::screen_resources const resources(
		_display,
		_window
	);

	awl::window::rect const window_rect(
		_window.rect()
	);

	sge::renderer::display_mode::optional_refresh_rate result;

	for(
		auto const &crtc
		:
		sge::opengl::xrandr::crtcs_view(
			resources
		)
	)
	{
		sge::opengl::xrandr::crtc_info const info(
			_display,
			resources,
			crtc
		);

		if(
			!fcppt::math::box::intersects(
				info.rect(),
				window_rect
			)
		)
			continue;

		for(
			auto const &mode
			:
			sge::opengl::xrandr::modes_view(
				resources
			)
		)
		{
			if(
				mode.id
				!=
				info.mode()
			)
				continue;

			result =
				sge::opengl::xrandr::combine_rates(
					result,
					sge::opengl::xrandr::refresh_rate_from_mode(
						mode
					)
				);
		}
	}

	return
		result;
}
