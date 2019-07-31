//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/d3d9/d3dinclude.hpp>
#include <sge/d3d9/convert/to_display_mode.hpp>
#include <sge/renderer/screen_size.hpp>
#include <sge/renderer/display_mode/object.hpp>
#include <sge/renderer/display_mode/optional_dimensions.hpp>
#include <sge/renderer/display_mode/optional_refresh_rate.hpp>
#include <sge/renderer/display_mode/pixel_size.hpp>
#include <sge/renderer/display_mode/refresh_rate.hpp>


sge::renderer::display_mode::object
sge::d3d9::convert::to_display_mode(
	D3DDISPLAYMODE const &_mode
)
{
	return
		sge::renderer::display_mode::object(
			sge::renderer::display_mode::pixel_size(
				sge::renderer::screen_size(
					_mode.Width,
					_mode.Height
				)
			),
			sge::renderer::display_mode::optional_dimensions(),
				_mode.RefreshRate
				==
				0u
				?
					sge::renderer::display_mode::optional_refresh_rate()
				:
					sge::renderer::display_mode::optional_refresh_rate(
						sge::renderer::display_mode::refresh_rate(
							_mode.RefreshRate
						)
					)
		);
}
