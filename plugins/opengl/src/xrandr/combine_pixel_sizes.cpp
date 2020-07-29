//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/opengl/xrandr/combine_pixel_sizes.hpp>
#include <sge/renderer/screen_size.hpp>
#include <sge/renderer/display_mode/optional_pixel_size.hpp>
#include <sge/renderer/display_mode/pixel_size.hpp>


sge::renderer::display_mode::optional_pixel_size
sge::opengl::xrandr::combine_pixel_sizes(
	sge::renderer::display_mode::optional_pixel_size const &_previous,
	sge::renderer::display_mode::pixel_size const &_next
)
{
	return
		_previous.has_value()
		?
			sge::renderer::display_mode::optional_pixel_size()
		:
			sge::renderer::display_mode::optional_pixel_size(
				_next
			)
		;
}
