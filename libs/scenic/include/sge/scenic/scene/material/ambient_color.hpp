//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_SCENIC_SCENE_MATERIAL_AMBIENT_COLOR_HPP_INCLUDED
#define SGE_SCENIC_SCENE_MATERIAL_AMBIENT_COLOR_HPP_INCLUDED

#include <sge/image/color/any/object.hpp>
#include <fcppt/declare_strong_typedef.hpp>
#include <fcppt/strong_typedef.hpp>

namespace sge::scenic::scene::material
{
FCPPT_DECLARE_STRONG_TYPEDEF(sge::image::color::any::object, ambient_color);
}

#endif
