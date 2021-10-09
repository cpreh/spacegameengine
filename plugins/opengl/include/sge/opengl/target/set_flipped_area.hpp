//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_OPENGL_TARGET_SET_FLIPPED_AREA_HPP_INCLUDED
#define SGE_OPENGL_TARGET_SET_FLIPPED_AREA_HPP_INCLUDED

#include <sge/opengl/target/area_function.hpp>
#include <sge/renderer/pixel_rect.hpp>
#include <sge/renderer/screen_unit.hpp>

namespace sge::opengl::target
{

void set_flipped_area(
    sge::opengl::target::area_function,
    sge::renderer::pixel_rect const &,
    sge::renderer::screen_unit);

}

#endif
