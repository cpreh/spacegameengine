//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/opengl/xrandr/combine_dimensions.hpp>
#include <sge/opengl/xrandr/combine_pixel_sizes.hpp>
#include <sge/opengl/xrandr/combine_rates.hpp>
#include <sge/opengl/xrandr/crtc_info.hpp>
#include <sge/opengl/xrandr/crtcs_view.hpp>
#include <sge/opengl/xrandr/current_display_mode.hpp>
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
#include <awl/backends/x11/window/base.hpp>
#include <awl/backends/x11/window/rect.hpp>
#include <fcppt/assert/error.hpp>
#include <fcppt/math/box/intersects.hpp>
#include <fcppt/math/dim/comparison.hpp>
#include <fcppt/math/dim/contents.hpp>
#include <fcppt/math/dim/null.hpp>
#include <fcppt/optional/map.hpp>
#include <fcppt/optional/maybe_void.hpp>
#include <fcppt/config/external_begin.hpp>
#include <X11/extensions/Xrandr.h>
#include <fcppt/config/external_end.hpp>


sge::renderer::display_mode::optional_object
sge::opengl::xrandr::current_display_mode(
	awl::backends::x11::window::base const &_window
)
{
	sge::opengl::xrandr::screen_resources const resources{
		_window
	};

	awl::backends::x11::window::rect const window_rect(
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
			_window.display(),
			resources,
			crtc
		);

		if(
			crtc_info.pixel_size()
			==
			sge::renderer::display_mode::pixel_size(
				fcppt::math::dim::null<
					sge::renderer::screen_size
				>()
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
				_window.display(),
				resources,
				output
			);

			if(
				fcppt::math::dim::contents(
					output_info.dimensions().get()
				)
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

	fcppt::optional::maybe_void(
		dimensions,
		[](
			sge::renderer::display_mode::dimensions const _dim
		)
		{
			FCPPT_ASSERT_ERROR(
				fcppt::math::dim::contents(
					_dim.get()
				)
				!=
				0u
			);
		}
	);

	return
		fcppt::optional::map(
			pixel_size,
			[
				dimensions,
				refresh_rate
			](
				sge::renderer::display_mode::pixel_size const _pixel_size
			)
			{
				return
					sge::renderer::display_mode::object(
						_pixel_size,
						dimensions,
						refresh_rate
					);
			}
		);
}
