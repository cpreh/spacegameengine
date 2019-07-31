//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/image/color/format.hpp>
#include <sge/opengl/vf/color_formats.hpp>
#include <sge/renderer/vf/dynamic/color_format_vector.hpp>


sge::renderer::vf::dynamic::color_format_vector
sge::opengl::vf::color_formats()
{
	return
		sge::renderer::vf::dynamic::color_format_vector{
			sge::image::color::format::rgb8,
			sge::image::color::format::rgba8,
			sge::image::color::format::rgb32f,
			sge::image::color::format::rgba32f
		};
}
