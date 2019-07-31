//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/image/color/format.hpp>
#include <sge/renderer/vf/dynamic/color.hpp>


sge::renderer::vf::dynamic::color::color(
	sge::image::color::format const _color_format
)
:
	color_format_(
		_color_format
	)
{
}

sge::image::color::format
sge::renderer::vf::dynamic::color::color_format() const
{
	return color_format_;
}
