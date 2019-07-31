//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/renderer/visual_base.hpp>
#include <sge/renderer/pixel_format/object.hpp>


sge::renderer::visual_base::visual_base(
	sge::renderer::pixel_format::object const &_pixel_format
)
:
	pixel_format_(
		_pixel_format
	)
{
}

sge::renderer::visual_base::~visual_base()
{
}

sge::renderer::pixel_format::object const &
sge::renderer::visual_base::pixel_format() const
{
	return
		pixel_format_;
}
