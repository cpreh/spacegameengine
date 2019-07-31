//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_OPENGL_VISUAL_CONVERT_COLOR_HPP_INCLUDED
#define SGE_OPENGL_VISUAL_CONVERT_COLOR_HPP_INCLUDED

#include <sge/opengl/visual/rgb_triple_fwd.hpp>
#include <sge/renderer/pixel_format/color_fwd.hpp>


namespace sge
{
namespace opengl
{
namespace visual
{

sge::opengl::visual::rgb_triple
convert_color(
	sge::renderer::pixel_format::color
);

}
}
}

#endif
