//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/d3d9/visual.hpp>
#include <sge/renderer/visual_base.hpp>
#include <sge/renderer/pixel_format/object_fwd.hpp>
#include <awl/backends/windows/visual/null_object.hpp>


sge::d3d9::visual::visual(
	sge::renderer::pixel_format::object const &_pixel_format
)
:
	awl::backends::windows::visual::null_object(),
	sge::renderer::visual_base(
		_pixel_format
	)
{
}

sge::d3d9::visual::~visual()
{
}
