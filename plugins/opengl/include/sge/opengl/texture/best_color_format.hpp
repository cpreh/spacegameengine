//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_OPENGL_TEXTURE_BEST_COLOR_FORMAT_HPP_INCLUDED
#define SGE_OPENGL_TEXTURE_BEST_COLOR_FORMAT_HPP_INCLUDED

#include <sge/image/color/format_fwd.hpp>
#include <sge/opengl/color_format.hpp>


namespace sge::opengl::texture
{

sge::opengl::color_format
best_color_format(
	sge::image::color::format
);

}

#endif
