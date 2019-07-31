//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/d3d9/visual.hpp>
#include <sge/d3d9/parameters/extract_pixel_format.hpp>
#include <sge/renderer/pixel_format/object.hpp>
#include <awl/visual/object.hpp>


sge::renderer::pixel_format::object
sge::d3d9::parameters::extract_pixel_format(
	awl::visual::object const &_visual
)
{
	// TODO: Is there a sane default if this fails?
	return
		dynamic_cast<
			sge::d3d9::visual const &
		>(
			_visual
		).pixel_format();
}
