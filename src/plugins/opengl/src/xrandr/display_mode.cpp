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


#include <sge/opengl/xrandr/combine_dimensions.hpp>
#include <sge/opengl/xrandr/combine_pixel_sizes.hpp>
#include <sge/opengl/xrandr/combine_rates.hpp>
#include <sge/opengl/xrandr/crtc_info.hpp>
#include <sge/opengl/xrandr/crtcs_view.hpp>
#include <sge/opengl/xrandr/display_mode.hpp>
#include <sge/opengl/xrandr/modes_view.hpp>
#include <sge/opengl/xrandr/output_info.hpp>
#include <sge/opengl/xrandr/outputs_view.hpp>
#include <sge/opengl/xrandr/refresh_rate_from_mode.hpp>
#include <sge/opengl/xrandr/screen_resources.hpp>
#include <sge/renderer/display_mode/object.hpp>
#include <sge/renderer/display_mode/optional_dimensions.hpp>
#include <sge/renderer/display_mode/optional_object.hpp>
#include <sge/renderer/display_mode/optional_pixel_size.hpp>
#include <sge/renderer/display_mode/optional_refresh_rate.hpp>
#include <sge/renderer/display_mode/pixel_size.hpp>
#include <awl/backends/x11/display_fwd.hpp>
#include <awl/backends/x11/window/object.hpp>
#include <awl/window/rect.hpp>
#include <fcppt/assert/error.hpp>
#include <fcppt/math/box/intersects.hpp>
#include <fcppt/math/dim/comparison.hpp>
#include <fcppt/config/external_begin.hpp>
#include <X11/extensions/Xrandr.h>
#include <fcppt/config/external_end.hpp>


sge::renderer::display_mode::optional_object const
sge::opengl::xrandr::display_mode(
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

	sge::renderer::display_mode::optional_pixel_size pixel_size;

	sge::renderer::display_mode::optional_refresh_rate refresh_rate;

	sge::renderer::display_mode::optional_dimensions dimensions;

	for(
		RRCrtc const crtc
		:
		sge::opengl::xrandr::crtcs_view(
			resources
		)
	)
	{
		sge::opengl::xrandr::crtc_info const crtc_info(
			_display,
			resources,
			crtc
		);

		if(
			crtc_info.pixel_size()
			==
			sge::renderer::display_mode::pixel_size(
				sge::renderer::screen_size::null()
			)
		)
			continue;

		pixel_size =
			sge::opengl::xrandr::combine_pixel_sizes(
				pixel_size,
				crtc_info.pixel_size()
			);

		if(
			!fcppt::math::box::intersects(
				crtc_info.rect(),
				window_rect
			)
		)
			continue;

		for(
			RROutput const output
			:
			sge::opengl::xrandr::outputs_view(
				resources
			)
		)
		{
			sge::opengl::xrandr::output_info const output_info(
				_display,
				resources,
				output
			);

			if(
				output_info.dimensions().get().content()
				==
				0u
			)
				continue;

			dimensions =
				sge::opengl::xrandr::combine_dimensions(
					dimensions,
					output_info.dimensions()
				);
		}

		for(
			XRRModeInfo const &mode
			:
			sge::opengl::xrandr::modes_view(
				resources
			)
		)
		{
			if(
				mode.id
				!=
				crtc_info.mode()
			)
				continue;

			refresh_rate =
				sge::opengl::xrandr::combine_rates(
					refresh_rate,
					sge::opengl::xrandr::refresh_rate_from_mode(
						mode
					)
				);
		}
	}

	FCPPT_ASSERT_ERROR(
		!dimensions
		||
		dimensions->get().content()
		!=
		0u
	);

	return
		pixel_size
		?
			sge::renderer::display_mode::optional_object(
				sge::renderer::display_mode::object(
					*pixel_size,
					dimensions,
					refresh_rate
				)
			)
		:
			sge::renderer::display_mode::optional_object()
		;
}
