//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_OPENGL_TARGET_READ_PIXELS_HPP_INCLUDED
#define SGE_OPENGL_TARGET_READ_PIXELS_HPP_INCLUDED

#include <sge/opengl/color_base_type.hpp>
#include <sge/opengl/color_order.hpp>
#include <sge/renderer/pixel_pos_fwd.hpp>
#include <sge/renderer/raw_pointer.hpp>
#include <sge/renderer/screen_size_fwd.hpp>


namespace sge
{
namespace opengl
{
namespace target
{

void
read_pixels(
	sge::renderer::pixel_pos,
	sge::renderer::screen_size,
	sge::opengl::color_order,
	sge::opengl::color_base_type,
	sge::renderer::raw_pointer
);

}
}
}

#endif
