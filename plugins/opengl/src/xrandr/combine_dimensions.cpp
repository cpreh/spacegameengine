//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/opengl/xrandr/combine_dimensions.hpp>
#include <sge/renderer/display_mode/dimensions.hpp>
#include <sge/renderer/display_mode/optional_dimensions.hpp>


sge::renderer::display_mode::optional_dimensions
sge::opengl::xrandr::combine_dimensions(
	sge::renderer::display_mode::optional_dimensions const &_previous,
	sge::renderer::display_mode::dimensions const &_next
)
{
	return
		_previous.has_value()
		?
			_previous
		:
			sge::renderer::display_mode::optional_dimensions(
				_next
			)
		;
}
